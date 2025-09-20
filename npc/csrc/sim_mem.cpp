
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "Core.h"
  #include "nemuInface.h"
extern "C" uint8_t pmem[0x10000000];
extern "C" void paddr_write(uint32_t addr, int len, uint32_t data);
extern "C"  uint32_t paddr_read(uint32_t addr, int len);

static unsigned long long last_time = 0000000000; 
static int r;
static int addr;
extern "C" void difftest_skip_next_inst_ref();

extern "C" int dpi_pmem_read(uint32_t raddr) {

	if (raddr == 0xa0000048) {
            difftest_skip_next_inst_ref();
	    return time(NULL);
	}

	if (raddr == 0xa000004c) {
            difftest_skip_next_inst_ref();
	    return time(NULL) >> 32;
	}

	r = paddr_read(raddr, 4);
//	printf("read addr :0x%x val: 0x%x \n", raddr, r);
	return (int) r;
}

extern Core * npcCore;
extern "C" void dpi_pmem_write(int waddr, int wdata, char wmask) {
  /*	
  if(last_time == ttime) {
  // printf("Repeatlly access addr:0x%x,data:0x%x\n" ,raddr,r);
     return;	
   }
   last_time = ttime; 
 */
  if(waddr == 0xa00003f8) { 
 //   printf("-----------------------------------PC: 0x%x, Write addr 0xa00003f8.-------------------------------------\n", cpu.pc);
    difftest_skip_next_inst_ref();
    putchar((char)wdata);
    fflush(stdout);
    return;
  }
  int len = 0;
  switch(wmask) {
	case 0b0001: len = 1; break;
	case 0b0011: len = 2; break;
        case 0b1111: len = 4; break;		     
	default: 
         printf("addr:0x%x", waddr);
		     printf("wmask:0x%x\n",wmask);
		     assert(0);		   
  } 
  //printf("addr:0x%x, data:0x%x,len:%d\n", waddr,wdata,len);
  paddr_write(waddr, len, wdata);
  return;
}
