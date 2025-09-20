import "DPI-C"  function void dpi_trigger_ftrace ();


module SimFtraceBlackBox(
    input    is_jal_jalr
);

 always @(is_jal_jalr) begin
    if (is_jal_jalr) begin
       dpi_trigger_ftrace();
    end
 end

endmodule
