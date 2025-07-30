import "DPI-C" pure function int  dpi_pmem_read (input int raddr);
import "DPI-C" function void dpi_pmem_write(input int waddr,
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
      rdata = dpi_pmem_read(raddr);
      if (wen) dpi_pmem_write(waddr, wdata, wmask);
    end else begin
      rdata = 32'b0;
    end
  end
endmodule

