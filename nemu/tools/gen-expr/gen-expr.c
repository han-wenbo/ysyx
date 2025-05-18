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
// this should be enough
static char buf[65536] = {};
static char tmp_buf[64] = {};
static char *buf_p = &buf[0];  // Point to the first address that is not be used.
static char *pre_p = &buf[0];   // Point to the second to last element.
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

uint32_t choose(uint32_t n){
  uint32_t r = (uint32_t)rand() % n;
  assert(r < n);
  return r; 
 
}

void gen_rand_space() {
  int i = 0;
  for(;i < choose(10) + 1; i++)
  {  
    //assert(*buf_p != '+' && *buf_p != '/' && *buf_p != '*' && *buf_p != '-');
    *buf_p++ = ' ';
  }
}

static void gen_rand_num() {
  uint32_t num = rand() % 8888;
  //assert(*buf_p != '+' && *buf_p != '/' && *buf_p != '*' && *buf_p != '-');
  /* if the operater is '/', then this number cannot be zero. */
  /*
  if(*pre_p == '/')
    num = (uint32_t)rand() + 1;
  else 
    num = (uint32_t)rand();
  */
  int str_len;
  switch(choose(2)){
    case 0: sprintf(tmp_buf, "0x%x", num);break;
    case 1:sprintf(tmp_buf, "%u", num); break;
  }
  str_len = strlen(tmp_buf);

  /* Insert space before a number */
  gen_rand_space();
  sprintf(buf_p, "%s", tmp_buf);
  buf_p += str_len; // Point to '/0'.

  gen_rand_space();
}

static void gen_rand_op(){
  pre_p = buf_p;
  switch(choose(4)) {
     case 0:  *buf_p++ = '+'; break;
     case 1:  *buf_p++ = '-'; break;
     case 2:  *buf_p++ = '/'; break;
     default:  *buf_p++ = '*';
  }
  gen_rand_space();
}

static void genchar_at_bufp(char c){
  //assert(buf_p != NULL && buf_p < buf+sizeof(buf));
  *buf_p++ = c;
}
static void gen_rand_expr() {

  /* if space is not enough, only generate number.*/
  if(buf_p - buf > 65536- 128){
    gen_rand_num();
    return; 
  }

  switch(choose(3)) {
    case 0:gen_rand_num(); break;
    case 1:gen_rand_expr();gen_rand_op();gen_rand_expr();break;
    case 2:genchar_at_bufp('(');gen_rand_expr();genchar_at_bufp(')');
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

  
    printf("%u %s\n", result, buf);
  
  }
 return 0;
}
