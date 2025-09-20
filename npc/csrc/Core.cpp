#include <verilated_vcd_c.h>
#include "Core.h"
#include "VCore.h"
//#include "verilated.h"
#include "nemuInface.h"
#include <csignal>
#include <iostream>
#include <cstdint>




const uint32_t Core::MEM_BASE = 0x80000000;
const uint32_t Core::MEM_MAX = Core::MEM_BASE + MEM_SIZE - 1;
const int Core::REGSNUM = 16;



void Core::doStep() {
          stepNum++;
	  /*** When reaching here, we must consider which instruction to be executed? ***/
	//  std::cout <<" **************************Before step, pc =  ******************************"<<std::hex << getPc()<<std::endl;
	  ttime++;
          vcore->clock = 0;
	  vcore->eval();
	  //contextp->timeInc(1);
	 // std::cout <<" **************************Middle step, pc =  ******************************"<<std::hex << getPc()<<std::endl;
	  //tfp->dump(static_cast<uint64_t>(ttime++));
	  //
	  extern void set_jal_jalr_occur();
	  set_jal_jalr_occur();

          vcore->clock = 1;
          vcore->eval();	
	  //contextp->timeInc(1);

	  //std::cout <<" **************************After step, pc =  ******************************"<<std::hex << getPc()<<std::endl;
	  //std::cout <<"After step, pc = "<<std::hex << getPc()<<std::endl;
	  //std::cout <<"time:"<<ttime<<std::endl;
     }

 void Core::stepWrReg(){
    doStep();
    for(int i = 1; i < 16; i++){
	cpu.gpr[i] = this->getReg(i);
    }
}
uint8_t * Core::coreAddr2Host(uint32_t addr) {
         assert(addr <= MEM_MAX || addr >= MEM_BASE);
         assert(pmem != NULL);
	 return (uint8_t *) ((uint64_t)addr -(uint64_t) MEM_BASE + (uint64_t)pmem);
     }

void Core::step(int n){
	for( int i = 0; i < n; i++) {
	   doStep();
	}
 }
      void Core::reset()  {
	 vcore->reset = 1;
	 std::cout << "reset!!" << std::endl;
	 doStep(); 
	 vcore->reset = 0;
      }


      void Core::setPc(uint32_t pc) {
         vcore->io_setPcEn = 1;
	 vcore->io_testSetPcVal = pc;
	 doStep();
	 vcore->io_setPcEn = 0;

	 //assert(vcore->io_instAddr == pc);
      }

      uint32_t Core::getPc() {
	 return vcore->io_instAddr;
      }

       void Core::setReg(int i, uint32_t val) {
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

#define GETREG_CASE(k) \
   case k: { \
     r = vcore->io_testReadRegs_##k; break; \
   } 

      uint32_t Core::getReg(int i){
          if( i > REGSNUM || i < 0) {
             std::cout<< "setReg arguments error! " << std::endl;
	     return -1;
	  }   
	uint32_t r;
	switch (i) {
            GETREG_CASE(0); 	  
            GETREG_CASE(1); 	  
            GETREG_CASE(2); 	  
            GETREG_CASE(3); 	  
            GETREG_CASE(4); 	  
            GETREG_CASE(5); 	  
            GETREG_CASE(6); 	  
            GETREG_CASE(7); 	  
            GETREG_CASE(8); 	  
            GETREG_CASE(9); 	  
            GETREG_CASE(10); 	  
            GETREG_CASE(11); 	  
            GETREG_CASE(12); 	  
            GETREG_CASE(13); 	  
            GETREG_CASE(14); 	  
            GETREG_CASE(15); 	  
	}
	/*  vcore->io_testRdIdx = i;
          vcore->clock = 0;
	  vcore->eval();*/
	  return r;
      }
      void Core::showAllReg() {
        for(int i = 0; i < REGSNUM; i++) {
	   std::cout << "Reg" << i << ":" <<  getReg(i) << std::endl; 
	}
      }
      uint32_t Core::memRead(uint32_t addr, int len) {
         uint8_t * localAddr = coreAddr2Host(addr); 
	 switch(len) {
           case 1: return *(uint8_t  *) localAddr;
           case 2: return *(uint16_t *) localAddr;
           case 4: return *(uint32_t *) localAddr;
	 }
	 assert(false);
      } 

      void Core::exN(int n) {
         // Off all test interfaces.
         vcore->io_testEn = false;
	 vcore->io_setPcEn = false;
 
	 for(int i = 0; i < n; i++) {
	    stepWrReg();
	 }
      }


Core::Core() :
   stepNum(0)
{
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



