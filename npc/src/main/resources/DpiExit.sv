module SimExitBlackBox(input logic triSg);
  import "DPI-C" function void sim_exit();

  logic prev;

  initial prev = 0;

  always @(triSg) begin
    if (triSg && !prev)
      sim_exit();
    prev = triSg;
  end
endmodule
