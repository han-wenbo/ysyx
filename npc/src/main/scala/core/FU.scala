package core
import chisel3._
import chisel3.util.HasBlackBoxInline
import core.control._
import chisel3.util._
class ImemDpi extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val reset   = Input(Reset())
    val addr = Input(UInt(32.W))
    val inst = Output(UInt(32.W))

    val clock = Input(Clock())

  })

  setInline("ImemDpi.v",
    s"""
      |module ImemDpi(
      |  input         reset,
      |  input  [31:0] addr,
      |  output reg  [31:0] inst,
      |  input clock 
      |);
      |  initial begin
      |// $$monitor(": resrt = %b, inst = %h", reset, inst);
      |end
      |  always @(addr) begin
      |    if (~reset) begin
      |     // $$display(" Fetch inst at %h", addr);
      |      inst = 32'hFFFF_FFFF;         
      |      inst = dpi_pmem_read(addr);   
      |    end
      |    else begin
      |      inst = 32'h0000_0013;         
      |    end
      |  end
      |endmodule
      |""".stripMargin)
}

class FU(enableTestInit : Boolean) extends Module {
   val io = IO(new Bundle { 

     //@instIn: the instrution which fecth by FU using @pc as address
     //val instIn   = Input(UInt(32.W))

     val toDU     = new FUtoDUIO
     val fromDU   = Flipped(new DUtoFUIO)

     val fromDUCtrl = Input(new DU2FUCtrl)
     // When branch is true or jmp occures, the next pc is @aluPc
     val aluPc    = Input(UInt(32.W))
      // 0: pc + 4
      // 1: the next pc is aluPc
     val pcSrcSel  = Input(Bool())


     val setPcEn   : Option[Bool] = if (enableTestInit) Some(Input(Bool())) else None
     val testSetPcVal : Option[UInt] = if (enableTestInit) Some(Input(UInt(32.W))) else None
   })

   val imem = Module(new ImemDpi)

   val pcReg = RegInit("h80000000".U(32.W))
   val snpc  = pcReg + 4.U

   /*  Now, pc has four resources:
    *     1) pc + 4;
    *     2) ALU  , including branch and jmp instructions;
    *     3) MTVEC, because of ecall;
    *     4) MEPC  , because of mret.
    *
    *     io.pcSrcSel being true indicates that pc should comes from the ALU.
    *     When io.fromDUCtrl.TrapInst.trapInst is true, it is obtained from MTVEC.
    *     When mret is exected, pc will be from the EPC.
    *
    *     These signals' high are mutally exclusive.
    *     Hence,I use a priority decoder, and then connecting it's output to a mux.
    */

   val pcMuxSel =    (io.fromDUCtrl.ToMepc.toMepc      ## 
                      io.fromDUCtrl.TrapInst.trapInst  ## 
                      io.pcSrcSel                      ## 
                      0.U(1.W))

   val dnpc  =  Wire(UInt(32.W))
   dnpc  :=  snpc
   switch(pcMuxSel) {
     is("b0010".U) { dnpc := io.aluPc }
     is("b0100".U) { dnpc := io.fromDU.vec  }
     is("b1000".U) { dnpc := io.fromDU.mepc }
   }
  


   imem.io.reset   := reset.asBool
   imem.io.addr := pcReg
   imem.io.clock := clock

   io.toDU.pc      := pcReg
   io.toDU.snpc    := snpc
   io.toDU.inst    := imem.io.inst
 
   val pcVal  = if (enableTestInit) Mux(io.setPcEn.get, io.testSetPcVal.get, dnpc) else dnpc
//   pcReg := pcVal
   
  pcReg := pcVal

}
