#include "VCore.h"
//#include "verilated.h"
#include <signal.h>
#include <csignal>
  #include "nemuInface.h"
#include "Core.h"
unsigned long long ttime;
Core * npcCore;
static void sig_handler(int n){
    if (npcCore->tfp) { npcCore->tfp->flush(); npcCore->tfp->close(); }
    _exit(n);                   // 用 _exit 避免再进 C++ 析构
}
static void trace_signal_init(){
    signal(SIGSEGV, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGINT , sig_handler);
}

extern "C" void npc_exec(Decode * s) {
  s->snpc += 4;
  s->isa.inst = npcCore->memRead(s->pc,4);
  npcCore->exN(1);
  s->dnpc = npcCore->getPc();
}

extern "C" void init_sim() {
//	 Verilated::traceEverOn(true);
	 npcCore = new Core;
//	 trace_signal_init();
}


