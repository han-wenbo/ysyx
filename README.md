## YSYX Project

- **Software – NEMU (RISC-V Simulator)**  
  - Independently developed an **RV32I instruction set simulator** in C, including peripheral models (**clock, keyboard, VGA**) and partial **libc support**  
  - Built debugging tools (**expression evaluator, watchpoints, instruction tracing**) and enabled execution of **CPU-test programs**  
  - Validated implementation through **instruction-level differential testing with Spike**  

- **Hardware – RV32E Processor (Chisel)**  
  - Independently designed and implemented a **single-cycle RV32E processor** in Chisel, supporting **47 RISC-V instructions**  
  - Achieved full compatibility with **CPU-test programs** and successfully ran the **RT-Thread operating system**  
  - Verified correctness with **instruction-level differential testing against Spike**  
  - Currently extending the design with **pipeline architecture, bus interface, and cache support**
