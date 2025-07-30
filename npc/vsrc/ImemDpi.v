
module ImemDpi(
  input  [31:0] addr,
  output [31:0] inst
);
  assign inst = dpi_pmem_read(addr);
endmodule