
#include <stdint.h>
#include <assert.h>
extern "C" uint8_t pmem[0x10000000];


extern "C"  uint32_t paddr_read(uint32_t addr, int len);
extern "C" uint32_t __pmem_read(uint32_t raddr) {
	return paddr_read(raddr, 4);
}
/*extern "C" {
    extern uint8_t* mem;   
} extern "C" uint8_t* coreAddr2Host(uint32_t addr) {
    return (uint8_t*)((uint64_t)addr - (uint64_t)0x80000000 + (uint64_t)mem);
}

extern "C" int pmem_read(int raddr) {
    uint8_t* localAddr = coreAddr2Host(raddr);
   printf("Read 0x%x from address 0x[%p]",*(uint32_t*) localAddr, localAddr );
    int len = 4;
    switch (len) {
        case 1: return *(uint8_t*)  localAddr;
        case 2: return *(uint16_t*) localAddr;
        case 4: return *(uint32_t*) localAddr;
        default:
            assert(false); // Invalid length
    }

    return 0; // Prevent compiler warning
}*/
extern "C" void __pmem_write(int waddr, int wdata, char wmask) {
  return;
}
