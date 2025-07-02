#include <svdpi.h>
#include <stdio.h>
int ebreak_triggered = 0;
extern "C" void sim_exit() {
    printf("[DPI-C] ebreak triggered. Simulation should exit.\n");
    ebreak_triggered = 1;
    fflush(stdout);
}


