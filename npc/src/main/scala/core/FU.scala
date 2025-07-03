package core
import chisel3._

class FU(enableTestInit : Boolean) extends Module {
   val io = IO(new Bundle { 
     val pc       = Output(UInt(32.W))
     val instIn   = Input(UInt(32.W))
     val instOut  = Output(UInt(32.W))
  
     val setPcEn   : Option[Bool] = if (enableTestInit) Some(Input(Bool())) else None
     val testSetPcVal : Option[UInt] = if (enableTestInit) Some(Input(UInt(32.W))) else None
   })

   val pcReg = RegInit("h80000000".U(32.W))

   io.instOut := io.instIn

   val pcVal  = if (enableTestInit) Mux(io.setPcEn.get, io.testSetPcVal.get, pcReg + 4.U) else pcReg + 4.U
   pcReg := pcVal

   io.pc := pcReg
}
