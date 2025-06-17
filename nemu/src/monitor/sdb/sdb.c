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

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
void show_point();
bool new_wp(char * s);
bool free_wp(int n);
word_t paddr_read(paddr_t addr, int len);
/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args){
  /* the number of setps that you want to Ex*/
  int i;

  if (args == NULL)
    cpu_exec(1);
  else {
    if((i = atoi(args)) <= 0) {
       printf("error");
       return -1;
    }
    cpu_exec(i);           
  }
  
  return 0;
}

static int cmd_info(char *args) {

  /* bug: args == NULL */
  if(strcmp(args, "r") == 0)
    isa_reg_display();
  if(strcmp(args, "w") == 0)
    show_point(); 
  return 0;
}
static int cmd_p(char *args){
  bool su;
  int val = expr(args, &su);
  if(!su){
     Log("Express error.");
     return 0;
  }
  printf("%d\n",val);
  return 0; 
}

static int cmd_watch(char * expr) {
  if(!new_wp(expr)) {
    printf("cmd_watch fail! \n");
    return 0;
  }
  return 0;
}

static int cmd_d(char * s) {
  char * endptr;
  long n = strtol(s,&endptr,10);

  if(n < 0 || endptr == s || *endptr != '\0') {
    printf("cmd_d: strtol error.\n");
 
  }

  if(!free_wp(n)) {
    printf("cmd_D fail! \n");
    return -1;
  }
 
  return 0;

}

static int cmd_x(char * s) {
  char *nump;
  char *addrp;

  nump = strtok(s, " ");
  addrp = strtok(NULL, " ");
  if(nump == NULL || addrp == NULL) {
     printf("arguments error!\n");
     return 0;
  }
  int num = strtol(nump, NULL, 10);
  bool success;
  paddr_t addr = (paddr_t) expr(addrp, &success);  
  if(!success) {
     Log("express error, Can't print memory.\n");
     return 0;
  }


  int q = num/4;
  int r = num % 4;
  assert(q * 4 + r == num);
  assert(q >= 0);
  assert(r >= 0);

  
  for(int i = 0; i < num; i += 4) {
    if( i % 16 == 0)
       printf("ADDRESSS: %08X", (uint) addr);

    printf("  %08X  ", paddr_read(addr, 4));

    
    if(i % 12 == 0 && i != 0) printf("\n");
    addr += 4;
  }
  if (r!=0)  printf("ADDRESS:0x%08X   0x%08X\n", (uint)addr, (uint)paddr_read(addr, 4));
  /*
  int q = num/16;
  int r = num % 16;
  assert(q * 4 + r == num);
  assert(q >= 0);
  assert(r >= 0);
  for(int i = 0; i < q; i++){
       printf("ADDRESS:0x%08X  0x%08X  0x%08X  0x%08X 0x%08X \n", 
              (uint)addr, 
              (uint)paddr_read(addr, 4),
              (uint)paddr_read(addr + 4, 4),
              (uint)paddr_read(addr + 8, 4),
              (uint)paddr_read(addr + 12,4));
       addr = addr +  16;
  }
  
  if(r != 0)
    printf("ADDRESS:0x%08X   0x%08X\n", (uint)addr, (uint)paddr_read(addr, 4)); */
  return 0;
}			
static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "excute [N] steps", cmd_si},
  { "info", "info r:print all regsiters. info w:print all watichpoints", cmd_info},
  { "p"   , "p EXPRESS", cmd_p},
  { "watch", "watch wp", cmd_watch},
  { "d", "delete watchpoint", cmd_d},
  { "x", "print memory, example: x 10 express", cmd_x} 
  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    /* strlen() don't count '\0'. */
    /* str_end points to '\0'*/
    char *str_end = str + strlen(str);


    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
