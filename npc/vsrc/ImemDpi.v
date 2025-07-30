
module ImemDpi(
  input         en,
  input  [31:0] addr,
  output reg  [31:0] inst
);
 always @(*) $display(" en=%b addr=%h", en, addr);
 wire [31:0] data = dpi_pmem_read(addr);
 assign inst = en ? data : 32'h0000_0013;
endmodule