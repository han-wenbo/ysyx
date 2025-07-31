#ifndef __SIM
#define __SIM

#include <verilated_vcd_c.h>
#include "VCore.h"
//#include "verilated.h"

#include <csignal>
#include <iostream>
#include <cstdint>
extern unsigned long long ttime;


typedef struct {
  uint32_t inst;
} riscv32_ISADecodeInfo;
typedef riscv32_ISADecodeInfo ISADecodeInfo;

typedef struct Decode {
  uint32_t pc;
  uint32_t snpc;
  uint32_t dnpc;
  ISADecodeInfo isa;
  char logbuf[256];
} Decode;


typedef struct {
  uint32_t gpr[32];
  uint32_t pc;
} riscv32_CPU_state;
extern "C" riscv32_CPU_state cpu;

extern "C" int  have_mem_access;
bool read_file(const std::string& s, uint8_t * buffer, long long bf_size);
 static const long long MEM_SIZE = 0x10000;
extern "C" uint8_t pmem[0x10000000];

class Core {
  private:
     static const uint32_t MEM_BASE = 0x80000000;
     static const uint32_t MEM_MAX  = MEM_BASE + MEM_SIZE - 1;
    
     static const int      REGSNUM  = 16;
     VerilatedContext* contextp;
     int stepNum = 0;
     VCore * vcore;

     void stepWrReg() {
	  doStep();
	  for(int i = 1; i < 16; i++){
	     cpu.gpr[i] = this->getReg(i);
	  }

     }
     void doStep() {
          stepNum++;
	  //std::cout <<"stepNum:"<<stepNum<<std::endl;
   
          vcore->clock = 0;
	  vcore->eval();
	  contextp->timeInc(1);
	  ttime++;
	  //tfp->dump(static_cast<uint64_t>(ttime++));
	 vcore->reset = 1;
          vcore->clock = 1;
          vcore->eval();	
	  contextp->timeInc(1);
	       }

     uint8_t * coreAddr2Host(uint32_t addr) {
         assert(addr <= MEM_MAX || addr >= MEM_BASE);
         assert(pmem != NULL);
	 return (uint8_t *) ((uint64_t)addr -(uint64_t) MEM_BASE + (uint64_t)pmem);
     }
     
     void exOnce(){
	 //uint32_t pc = vcore->io_instAddr;
	 //uint32_t inst = memRead(pc,4);
        
	 //std::cout << "PC:0x" << std::hex << pc 
         // << ", inst:0x" << inst << std::dec << std::endl; 
         //vcore->io_instIn = inst;
	 //doStep();
	 stepWrReg();
      } 

  public: 
     VerilatedVcdC* tfp;
      Core() {
        contextp = new VerilatedContext;
	contextp->debug(4); 
      //  contextp->traceEverOn(true);
        vcore = new VCore(contextp);

//	tfp = new VerilatedVcdC;
 //       vcore->trace(tfp, 99);	
//	tfp->open("wave.vcd");
	this->reset();
	have_mem_access = 0;
      }
      void setp(int n){
	for( int i = 0; i < n; i++) {
	   doStep();
	}
      }

      void reset()  {
	 std::cout << "reset!!" << std::endl;
	 doStep(); 
	 vcore->reset = 0;
      }


      void setPc(uint32_t pc) {
         vcore->io_setPcEn = 1;
	 vcore->io_testSetPcVal = pc;
	 doStep();
	 vcore->io_setPcEn = 0;

	 //assert(vcore->io_instAddr == pc);
      }

      uint32_t getPc() {
	 return vcore->io_instAddr;
      }
      // Writing to a register requires advancing the clock cycle, 
      // but since that also increments the PC, we need to make sure the PC stays the same 
      void setReg(int i, uint32_t val) {
	  if( i > REGSNUM || i < 0) {
             std::cout<< "setReg arguments error! " << std::endl;
	     return;
	  }
	  uint32_t pc = getPc();
	  vcore->io_testEn  = true;
	  vcore->io_testVal = val;
	  vcore->io_testIdx = i;
	  doStep();
	  vcore->io_testEn  = false;

	  vcore->io_setPcEn = true;
	  vcore->io_testSetPcVal = pc;
	  doStep();
	  vcore->io_setPcEn = false;

          assert(getPc() == pc);
	  
	  if(i != 0) assert(getReg(i) == val);

      }

      uint32_t getReg(int i){
          if( i > REGSNUM || i < 0) {
             std::cout<< "setReg arguments error! " << std::endl;
	     return -1;
	  }   
	  vcore->io_testRdIdx = i;
	  vcore->eval();
	  return vcore->io_testRdVal;
      }
      void showAllReg() {
        for(int i = 0; i < REGSNUM; i++) {
	   std::cout << "Reg" << i << ":" <<  getReg(i) << std::endl; 
	}
      }
      
      uint32_t memRead(uint32_t addr, int len) {
         uint8_t * localAddr = coreAddr2Host(addr); 
	 switch(len) {
           case 1: return *(uint8_t  *) localAddr;
           case 2: return *(uint16_t *) localAddr;
           case 4: return *(uint32_t *) localAddr;
	 }
	 assert(false);
      } 
      
      void exN(int n) {
         // Off all test interfaces.
         vcore->io_testEn = false;
	 vcore->io_setPcEn = false;
 
	 for(int i = 0; i < n; i++) {
            exOnce();
	 }
      }

};

#endif
