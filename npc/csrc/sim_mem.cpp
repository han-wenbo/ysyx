
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
extern "C" {
    extern uint8_t* mem;   
}
extern "C" uint8_t* coreAddr2Host(uint32_t addr) {
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
}
extern "C" void pmem_write(int waddr, int wdata, char wmask) {
  return;
}
