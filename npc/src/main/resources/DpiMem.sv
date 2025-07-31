import "DPI-C" pure function int  dpi_pmem_read (input int raddr);
import "DPI-C" function void dpi_pmem_write(input int waddr,
                                        input int wdata,
                                        input byte wmask,input int enable);


module MemContrl(
    input  clk,
    input         valid,
    input         wen,
    input  [31:0] raddr,
    input  [31:0] waddr,
    input  [31:0] wdata,
    input  [7:0]  wmask,
    output reg [31:0] rdata
);

always @(*) begin
    if (valid) begin
        rdata = dpi_pmem_read(raddr);
        if (wen) begin
            dpi_pmem_write(waddr, wdata, wmask,wen ? 32'h1 : 32'h0);
        end
    end else begin
        rdata = 32'b0;
    end
end

endmodule
