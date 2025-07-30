package core
import chisel3._


class ImemDpi extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr = Input(UInt(32.W))
    val inst = Output(UInt(32.W))
  })

  setInline("ImemDpi.v",
    s"""
      |import "DPI-C" function int dpi_pmem_read(input int raddr);
      |
      |module ImemDpi(
      |  input  [31:0] addr,
      |  output [31:0] inst
      |);
      |  assign inst = pmem_read(addr);
      |endmodule
      |""".stripMargin)
}

class FU(enableTestInit : Boolean) extends Module {
   val io = IO(new Bundle { 

     //@instIn: the instrution which fecth by FU using @pc as address
     //val instIn   = Input(UInt(32.W))

     val toDU     = new FUtoDUIO
    
     // When branch is true or jmp occures, the next pc is @aluPc
     val aluPc    = Input(UInt(32.W))
     // 0: pc + 4
     // 1: the next pc is aluPc
     val pcSrcSel  = Input(Bool())


     val setPcEn   : Option[Bool] = if (enableTestInit) Some(Input(Bool())) else None
     val testSetPcVal : Option[UInt] = if (enableTestInit) Some(Input(UInt(32.W))) else None
   })

   val imem = Module(new ImemDpi)
   imem.io.addr := pcReg

   val pcReg = RegInit("h80000000".U(32.W))
   val snpc  = pcReg + 4.U
   val dnpc  = io.aluPc

   io.toDU.pc := pcReg
   
   io.toDU.snpc    := snpc
   io.toDU.inst := imem.io.inst
 
   val pcRaw  =  Mux(io.pcSrcSel, dnpc, snpc)
   val pcVal  = if (enableTestInit) Mux(io.setPcEn.get, io.testSetPcVal.get, pcRaw) else pcRaw
   pcReg := pcVal

}
