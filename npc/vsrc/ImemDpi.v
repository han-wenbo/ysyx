
module ImemDpi(
  input         en,
  input  [31:0] addr,
  output reg  [31:0] inst
);
 always @(*) $display(" en=%b addr=%h", en, addr);
   assign inst = en ? dpi_pmem_read(addr) : 32'h0000_0013;
endmodule