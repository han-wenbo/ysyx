#include <svdpi.h>
#include <stdio.h>
#include <stdint.h>
#include "sim.h"

extern Core npcCore;
extern "C" void set_nemu_state(int state, uint32_t pc, int halt_ret);
extern "C" void sim_exit() {
    printf("[DPI-C] ebreak triggered. Simulation should exit.\n");
    fflush(stdout);
    set_nemu_state(2, cpu.pc, cpu.gpr[10]);
}


