#ifndef __NEMU__INTERFACE
#define __NEMU__INTERFACE 
extern unsigned long long ttime;
typedef struct {  uint32_t inst;
} riscv32_ISADecodeInfo;typedef riscv32_ISADecodeInfo ISADecodeInfo;
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
#endif
