
module ImemDpi(
  input         reset,
  input  [31:0] addr,
  output reg  [31:0] inst,
  input clock 
);
  initial begin
// $monitor(": resrt = %b, inst = %h", reset, inst);
end
  always @(addr) begin
    if (~reset) begin
     // $display(" Fetch inst at %h", addr);
      inst = 32'hFFFF_FFFF;         
      inst = dpi_pmem_read(addr);   
    end
    else begin
      inst = 32'h0000_0013;         
    end
  end
endmodule