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

#include "utils.h"
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include <stdio.h>
#include <structure.h>
/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 30
CPU_state cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;

// When pmem_read or pmem_write are called, they will set 
// these two varibales.
// Afterwards, in function exec_once(), they are checked.
int have_mem_access = 0;
paddr_t mem_access_addr = 0;

#ifdef CONFIG_ITRACE_RINGBUF
ringbuf_t inst_rb;
#endif

void device_update();
void lookthrough_wp();


typedef struct {
  // caller function's symbol index
  size_t func_idx; 
  uint32_t ret_addr;
} call_stack_element;

call_stack_element call_stack[50];
int call_dep = 0;

int jal_jalr_occur = 0;
extern symtab_for_func symtab;

static inline void ftrace(vaddr_t last_inst_pc, vaddr_t dnpc) {
  char buf[128];
  char * p = buf; 
  const char * func_name;
  p += sprintf(p, "0x%x", last_inst_pc);
  // Add call_dep number of space at the beginning to make it easier to read.
    
  // If function call occurs:
  if(jal_jalr_occur == 1) {
    jal_jalr_occur = 0;
    if(is_func_start(dnpc, &symtab) && cpu.gpr[1] == last_inst_pc + 4){ 
      memset(p, ' ', call_dep * 3);
      p += call_dep * 3;

      func_name = star_add2fcun_name(dnpc, &symtab); 
   
      assert(func_name != NULL);
      assert(strcmp(func_name,"???") != 0);

      call_stack[call_dep].ret_addr = last_inst_pc + 4; 
      call_stack[call_dep].func_idx = addr2idx(last_inst_pc, &symtab); 
      sprintf(p, "[%d]call:%s\n",call_dep, func_name);
      puts(buf);
      ftrace_write("%s", buf); 
      
      call_dep++;
     }
     //printf("::::::::::call_dep:%d, stack[%d].ret_addr = %x, dnpc=%x,lastpc = %x\n",call_dep,call_dep-1,call_stack[call_dep-1].ret_addr,dnpc, last_inst_pc );
     if(call_dep > 0 && dnpc == call_stack[call_dep-1].ret_addr){

       call_dep--;
       memset(p, ' ', call_dep * 3);
       p += call_dep * 3;

       func_name = star_add2fcun_name(last_inst_pc, &symtab); 
       sprintf(p, "[%d]ret from:%s\n",call_dep, func_name);
       puts(buf);
       ftrace_write("%s", buf); 

     }
  }
  assert(call_dep >= 0);
}

static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  // ITRACE_COND is defined by Makefile, and its value is CONFIG_ITRACE_COND without quote.
  if (ITRACE_COND) { 
    log_write("%s\n", _this->logbuf);
  }
#endif
 
// CONFIG_ITRACE_RINGBUF depends on CONFIG_ITRACE
 #ifdef CONFIG_ITRACE_RINGBUF  
  ringbuf_enq(&inst_rb, _this->logbuf);
 #endif

  ftrace(_this->pc, dnpc);

  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
  // first argument: the address of the instruction that was just executed.
  // the second: the address of the next instruction to be executed. 
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));
  lookthrough_wp();
}

void npc_exec(Decode *s);
static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;
  s->snpc = pc;
  npc_exec(s);
  //isa_exec_once(s);
  cpu.pc = s->dnpc;
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst;
#ifdef CONFIG_ISA_x86
  for (i = 0; i < ilen; i ++) {
#else
  for (i = ilen - 1; i >= 0; i --) {
#endif
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;

  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst, ilen);
 // Record memory accesses that are caused by ld and st.
 char * memlog_buf = s->logbuf + strlen(s->logbuf);
 assert( *memlog_buf == '\0');
 if(have_mem_access == 2) { 
    sprintf(memlog_buf,"\n   --->  Access memory address:0x%x" , mem_access_addr);
  }
  have_mem_access = 0;

#endif
}

static void execute(uint64_t n) {
  Decode s;
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    // Count the number of instructions that were exeuted.
    g_nr_guest_inst ++;
    trace_and_difftest(&s, cpu.pc);
    if (nemu_state.state != NEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void assert_fail_msg() {
  isa_reg_display();
  statistic();
}

#ifdef CONFIG_ITRACE_RINGBUF 
static void inst_rb_cb (void * element, void * p_call_num) {
  int n = (*(int *) p_call_num)++;
  if((n + 1 == inst_rb.head) || ((inst_rb.head == 0) && n + 1 == inst_rb.capacity))  
     ringbuf_log_write("<<<<<<============= The last instrction ============>>>>"); 
  ringbuf_log_write("%s\n",(char *) element); 
  return;
}
#endif

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT: case NEMU_QUIT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();

  execute(n);

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;
    case NEMU_END: case NEMU_ABORT: {
      // Write the contents of the instruction ring buffer to log file.
#ifdef CONFIG_ITRACE_RINGBUF
      int call_num = 0;
      ringbuf_log_write("==============================RING BUFFER==================================\n");
      ringbuf_foreach(&inst_rb, inst_rb_cb, &call_num);
#endif
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc); 
                                    }
      // fall through
    case NEMU_QUIT: statistic();
  }
}
