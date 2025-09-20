#include <svdpi.h>
#include <stdio.h>
#include <stdint.h>
#include "Core.h"
#include "nemuInface.h"
#define sb 1
extern Core npcCore;
extern "C" void set_nemu_state(int state, uint32_t pc, int halt_ret);
extern "C" void sim_exit() {
    printf("[DPI-C] ebreak triggered. Simulation should exit.\n");
    fflush(stdout);
    set_nemu_state(2, cpu.pc, cpu.gpr[10]);
}


