/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>

#define MEM_START 0x80000000
#define MEM_END 0x87ffffff 
#define MEM_SIZE MEM_END - MEM_START + 1
#define GUEST2HOST(a) ((mem) + (a - MEM_START))  


#define REG_N sizeof(regs)/sizeof(regs[0])
const char *regs[] = {
  "0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};
uint32_t reg[REG_N] = {};
char mem[MEM_SIZE] = {};


// this should be enough
static char buf[65536] = {};
static char buf_nemu[65536] = {};

static char tmp_buf[64] = {};
static char *buf_p = &buf[0];  // Point to the first address that is not be used.
static char *pre_p = &buf[0];   // Point to the second to last element.

static char *buf_nemu_p = &buf_nemu[0];
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int init_mem() {
 
  /* Memery size must be the mutiplication of 4. */
  assert(MEM_SIZE % 4 == 0);
  
  for(uint32_t * add = (uint32_t *)mem; add <= MEM_END; add ++) {
    *add = choose(UINT32_MAX);   
  }
  FILE *fp = fopen("./mem", "w");
  if(fp == NULL) {
    printf("Open mem fail! \n");
    return -1; 
  }

  if(fwrite(mem, sizeof(mem[0]), sizeof(mem)/sizeof(mem[0]), fp) < sizeof(mem)/sizeof(mem[0])) {
    printf("Write mem fail");
    return -1;
  }
  return 0;
}

int init_reg(){
  reg[0] = 0;
  
  for(int i = 1; i < REG_N; i++) {
    reg[i] = choose(UINT32_MAX);
  }
  FILE *fp = fopen("./reg", "w");
  if( fp == NULL) {
    printf("Open reg fail \n");
    return -1;
  }
 
  int wn = fwrite(reg, sizeof(reg[0]), sizeof(reg)/sizeof(reg[0]), fp);
  if(wn < sizeof(reg)/sizeof(reg[0])) {
    printf("Write reg fail\n");
    return -1;
  }
  return 0;
}


/* Randomly generate a number which is smaller than n */
uint32_t choose(uint32_t n){
  uint32_t r = (uint32_t)rand() % n;
  assert(r < n);
  return r; 
 
}
/* Randomly generate a number in [a,b]. */
uint32_t choose2(uint32_t a, uint32_t b) {
   assert(b >= a);
   uint32_t r = k + rand() % (n - k + 1);
   assert(r >= a && r <= b);
   return r;
}


void gen_rand_space() {
  int i = 0;
  for(;i < choose(10) + 1; i++)
  {  
    //assert(*buf_p != '+' && *buf_p != '/' && *buf_p != '*' && *buf_p != '-');
    *buf_p++ = ' ';
    *buf_nemu_p++ = ' ';
  }
}

static void gen_rand_num() {
  uint32_t num = rand() % 8888;
  int str_len;
  switch(choose(2)){
    case 0:sprintf(tmp_buf, "0x%x", num);
           break;
    case 1:sprintf(tmp_buf, "%u", num); break;
  }
  str_len = strlen(tmp_buf);

  /* Insert space before a number */
  gen_rand_space();
  sprintf(buf_p, "%s", tmp_buf);
  sprintf(buf_nemu_p, "%s", tmp_buf);
  buf_p += str_len; // Point to '/0'.
  buf_nemu_p += str_len;
  gen_rand_space();
}

static void gen_rand_op(){
  pre_p = buf_p;
  switch(choose(4)) {
     case 0:  genchar_at_bufp('+'); break;
     case 1:  genchar_at_bufp('-'); break;
     case 2:  genchar_at_bufp('/'); break;
     default: genchar_at_bufp('*');
  }
  gen_rand_space();
}

static void genchar_at_bufp(char c){
  //assert(buf_p != NULL && buf_p < buf+sizeof(buf));
  *buf_p++ = c;
  *buf_nemu_p++ = c
}

static void gen_rand_reg_access() {
  char tmp_buf[64];
  int reg_n = choose(REG_N);
  uint32_t reg_value = reg[reg_n];
  
  /* Write the ascii of the value stored in the register into buf */  
  switch(choose(2)) {
    case 0: sprintf(tmp_buf, "0x%x", reg_value);break;
    case 1: sprintf(tmp_buf, "%u", reg_value);
  }

  sprintf(buf_p,"%s",tmp_buf);
  buf_p += strlen(tmp_buf);
  assert(buf_p == '\0');


  /* Write register name into buf_nemu */
  sprintf(tmp_buf, "$%s",reg[reg_n]);
  sprintf(buf_nemu_p, "%s", tmp_buf);
  buf_nemu_p += strlen(tmp_buf);
  assert(buf_nemu_p == '\0'); 
  
}

static void gen_rand_mem_access() {
  char tmp_buf[64];
  uint32_t addr = choose2(MEM_START,MEM_END - 3);
  /* Write the ascii of *addr into buf_nemu. */
  switch(choose(2)) {
     case 0: sprintf(tmp_buf, "*0x%x", addr); break;
     case 1: sprintf(tmp_buf, "*%u", addr); 
  }

  sprintf(buf_nemu_p, "%s", tmp_buf);
  buf_nemu_p += strlen(tmp_buf);
  assert(buf_nemu_p == '\0');

  /* Write the ascii of the value stored in addr into buf */
  uint32_t * host_addr = GUEST2HOST(addr);
  assert((host_addr >= mem) && (host_addr <= mem + MEM_SIZE));
  uint32_t value = *host_addr;
  
  switch(choose(2)) {
     case 0: sprintf(tmp_buf, "*0x%x", value); break;
     case 1: sprintf(tmp_buf, "*%u", value); 
  }
  sprintf(buf_p, "%s", tmp_buf);
  buf_p += strlen(tmp_buf);
  assert(buf_p == '\0');
 
}
static void gen_rand_expr() {

  /* if space is not enough, only generate number.*/
  if(buf_p - buf < 128 || buf_nemu_p - buf_nemu < 128){
    gen_rand_num();
    return; 
  }

  switch(choose(5)) {
    case 0:gen_rand_num(); break;
    case 1:gen_rand_expr();gen_rand_op();gen_rand_expr();break;
    case 2:genchar_at_bufp('(');gen_rand_expr();genchar_at_bufp(')');
    case 3:gen_rand_reg_access();
    case 4:gen_rand_mem_access();
    default:return;
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    // memset(buf, 0, sizeof(buf));
    buf_p = &buf[0];
    
    gen_rand_expr();
    *buf_p = '\0';
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    //fp = popen("./test", "r")
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);

    /* closed by didve zero */
    int status = WEXITSTATUS(pclose(fp));
    if(WIFSIGNALED(status)) {
        if(WTERMSIG(status) ==  SIGFPE){
          continue;
        }
    }

  
    printf("%u %s\n", result, buf_nemu);
  
  }
 return 0;
}
