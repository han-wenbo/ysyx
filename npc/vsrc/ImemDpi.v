
module ImemDpi(
  input         en,
  input  [31:0] addr,
  output reg  [31:0] inst
);
    always @(*) begin
    if (en === 1'b1)
      inst = dpi_pmem_read(addr);   
    else
      inst = 32'h0000_0013;         
  end
endmodule