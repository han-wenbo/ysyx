module DpiExit(input logic trigger);
  import "DPI-C" function void sim_exit();

  logic prev;

  initial prev = 0;

  always @(trigger) begin
    if (trigger && !prev)
      sim_exit();
    prev = trigger;
  end
endmodule
