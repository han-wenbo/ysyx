import "DPI-C" pure function int  dpi_pmem_read (input int raddr);
import "DPI-C" function void dpi_pmem_write(input int waddr,
                                        input int wdata,
                                        input byte wmask);


module MemContrl(
    input         clk,
    input         valid,
    input         wen,
    input  [31:0] raddr,
    input  [31:0] waddr,
    input  [31:0] wdata,
    input  [7:0]  wmask,
    output reg [31:0] rdata
);

    // ─── 异步读：组合逻辑，同拍即可得到数据 ──────────────────────
    always @(*) begin
        if (valid)
            rdata = dpi_pmem_read(raddr);   // 纯函数，可安全多次调用
        else
            rdata = 32'b0;
    end

    // ─── 同步写：有副作用的 pmem_write 只在时钟沿执行一次 ────────
    always @(posedge clk) begin
        if (valid && wen)
            dpi_pmem_write(waddr, wdata, wmask);   // 不再出现“连环 store”
    end
endmodule
