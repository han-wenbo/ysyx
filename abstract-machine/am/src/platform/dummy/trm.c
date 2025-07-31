#include <am.h>
# define npc_trap(code) asm volatile("mv a0, %0; ebreak" : :"r"(code)) 
static const char mainargs[MAINARGS_MAX_LEN] = MAINARGS_PLACEHOLDER; // defined in CFLAGS
//Area heap = RANGE(NULL, NULL);
int main(const char * args);

void putch(char ch) {
}

void halt(int code) {
  npc_trap(code);

  // should not reach here
  while (1);
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
