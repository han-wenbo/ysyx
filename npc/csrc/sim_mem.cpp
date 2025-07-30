
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "sim.h"
extern "C" uint8_t pmem[0x10000000];
extern "C" void paddr_write(uint32_t addr, int len, uint32_t data);
extern "C"  uint32_t paddr_read(uint32_t addr, int len);
static unsigned long long last_time = 0000000000; 
static int r;
static int addr;
extern "C" int dpi_pmem_read(uint32_t raddr) {
        printf("access addr:0x%x\n" ,raddr);
	/*
        if(last_time == ttime) {
          // printf("Repeatlly access addr:0x%x,data:0x%x\n" ,raddr,r);
	   return r;	
	}
	last_time = ttime; */
	//if(raddr == 0) return 0;
//	r = paddr_read(raddr, 4);
	//printf("read addr:%x, data:%x\n", raddr,r);
	return 0; 
//	return (int) r;
}

extern "C" void dpi_pmem_write(int waddr, int wdata, char wmask) {
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
