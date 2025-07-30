
module ImemDpi(
  input         en,
  input  [31:0] addr,
  output [31:0] inst
);
  assign inst = en ? dpi_pmem_read(addr) : 32'h00000013;
endmodule