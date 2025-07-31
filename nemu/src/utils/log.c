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

#include "debug.h"
#include <common.h>
#include <stdint.h>
#include <stdio.h>
#include <structure.h>

extern ringbuf_t inst_rb;
extern uint64_t g_nr_guest_inst;

#ifndef CONFIG_TARGET_AM
FILE *log_fp = NULL;
void init_log(const char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    log_fp = fp;
   
#ifdef CONFIG_ITRACE_RINGBUF
    if(!ringbuf_init(&inst_rb, CONFIG_ITRACE_RINGBUF_NUM, 200)) Assert(fp, "Can not initlize instruction ring buffer!\n");
#endif
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}



bool log_enable() {
  return MUXDEF(CONFIG_TRACE, (g_nr_guest_inst >= CONFIG_TRACE_START) &&
         (g_nr_guest_inst <= CONFIG_TRACE_END), false);
}
#endif


FILE *dtrace_log_fp = NULL;
void init_dtrace_log(const char *log_file) {
  dtrace_log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    dtrace_log_fp = fp;
  }
  Log("Dtrace log is written to %s", log_file ? log_file : "stdout");
}
