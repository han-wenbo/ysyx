#ifndef __SIM_CLASS_CORE
#define __SIM_CLASS_CORE

#include <verilated_vcd_c.h>
#include "VCore.h"
//#include "verilated.h"

#include <csignal>
#include <iostream>
#include <cstdint>

class Core {
   private:
     static const uint32_t MEM_BASE;
     static const uint32_t MEM_MAX;
     static const int      REGSNUM;
     VerilatedContext* contextp;
     int stepNum;
     VCore * vcore;

     void stepWrReg();
     void doStep();
     uint8_t * coreAddr2Host(uint32_t addr);

   public:
     VerilatedVcdC* tfp;
     Core();
     void step(int n);
     void reset();
     void setPc(uint32_t pc);
     uint32_t getPc(); 
     void setReg(int i, uint32_t);
     uint32_t getReg(int i);
     uint32_t memRead(uint32_t addr, int len);
     void showAllReg();
     void exN(int n);
};
#endif
