import "DPI-C" function int  pmem_read (input int raddr);
import "DPI-C" function void pmem_write(input int waddr,
                                        input int wdata,
                                        input byte wmask);

module MemContrl (
    input  logic        valid,
    input  logic [31:0] raddr,
    input  logic        wen,
    input  logic [31:0] waddr,
    input  logic [31:0] wdata,
    input  logic  [7:0] wmask,
    output logic [31:0] rdata
);

  always @(*) begin
    if (valid) begin
      rdata = pmem_read(raddr);
      if (wen) pmem_write(waddr, wdata, wmask);
    end else begin
      rdata = 32'b0;
    end
  end
endmodule

