module SimExitBlackBox(input logic triSg,input logic clock);
  import "DPI-C" function void sim_exit();


  always @(triSg) begin
    if (triSg)
      sim_exit();
  end
endmodule
