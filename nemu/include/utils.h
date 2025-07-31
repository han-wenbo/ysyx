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

#include </usr/include/elf.h>
#ifndef __UTILS_H__
#define __UTILS_H__

#include <common.h>
#include <stdio.h>
//typedef uint32_t Elf32_Addr;
// ----------- state -----------

enum { NEMU_RUNNING, NEMU_STOP, NEMU_END, NEMU_ABORT, NEMU_QUIT };

typedef struct {
  int state;
  vaddr_t halt_pc;
  uint32_t halt_ret;
} NEMUState;

extern NEMUState nemu_state;

// ----------- timer -----------

uint64_t get_time();

// ----------- log -----------

#define ANSI_FG_BLACK   "\33[1;30m"
#define ANSI_FG_RED     "\33[1;31m"
#define ANSI_FG_GREEN   "\33[1;32m"
#define ANSI_FG_YELLOW  "\33[1;33m"
#define ANSI_FG_BLUE    "\33[1;34m"
#define ANSI_FG_MAGENTA "\33[1;35m"
#define ANSI_FG_CYAN    "\33[1;36m"
#define ANSI_FG_WHITE   "\33[1;37m"
#define ANSI_BG_BLACK   "\33[1;40m"
#define ANSI_BG_RED     "\33[1;41m"
#define ANSI_BG_GREEN   "\33[1;42m"
#define ANSI_BG_YELLOW  "\33[1;43m"
#define ANSI_BG_BLUE    "\33[1;44m"
#define ANSI_BG_MAGENTA "\33[1;45m"
#define ANSI_BG_CYAN    "\33[1;46m"
#define ANSI_BG_WHITE   "\33[1;47m"
#define ANSI_NONE       "\33[0m"

#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

#define log_write(...) IFDEF(CONFIG_TARGET_NATIVE_ELF, \
  do { \
    extern FILE* log_fp; \
    extern bool log_enable(); \
    if (log_enable() && log_fp != NULL) { \
      fprintf(log_fp, __VA_ARGS__); \
      fflush(log_fp); \
    } \
  } while (0) \
)

#define _Log(...) \
  do { \
    printf(__VA_ARGS__); \
    log_write(__VA_ARGS__); \
  } while (0)


// This macor is not affected by log_enable() .
#define ringbuf_log_write(...) \
  do {                                     \
    extern FILE* log_fp;                   \
    if(log_fp != NULL) {                \
       fprintf(log_fp, __VA_ARGS__);       \
    }                                      \
  } while(0)




// -----------------ftrace-----------------------

#define MAX_FUNC 200
typedef struct {
  Elf32_Addr start;
  Elf32_Addr end;
  char name [32];
} symtab_for_func_map;

typedef struct {
  symtab_for_func_map s_map[MAX_FUNC];
  size_t funcs_num; 
}symtab_for_func;

bool init_symtab_for_func_map(char * elf_name, symtab_for_func * st_m);
Elf32_Addr func_name2star_addr(char * func_name, symtab_for_func * st); 
const char * star_add2fcun_name(Elf32_Addr addr, symtab_for_func * st); 
void init_ftrace_file(char *name);
bool is_func_start(Elf32_Addr addr, symtab_for_func *st);
bool is_func_end(Elf32_Addr addr, symtab_for_func *st);
size_t addr2idx(Elf32_Addr addr, symtab_for_func *st);

#define ftrace_write(...)                 \
  do {                                    \
    extern FILE * ftrace_file_fp;              \
    if(ftrace_file_fp != NULL) {                      \
      fprintf(ftrace_file_fp,__VA_ARGS__);     \
      fflush(ftrace_file_fp);\
    }                                     \
  } while (0)


#define dtrace_write(...)                 \
  do {                                    \
    extern FILE * dtrace_log_fp;              \
    if(dtrace_log_fp != NULL) {                      \
      fprintf(dtrace_log_fp,__VA_ARGS__);     \
      fflush(dtrace_log_fp);\
    }                                     \
  } while (0)



#endif
