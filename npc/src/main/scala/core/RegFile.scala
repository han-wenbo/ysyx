package core
import chisel3._
import core.control._
import chisel3.util.log2Ceil
import java.lang
class RegFile (val enableTestInit : Boolean = false,val numRegs : Int) extends Module {

  val io = IO(new Bundle{
      val rregIdx1 = Input(UInt(log2Ceil(numRegs).W))
      val rregIdx2 = Input(UInt(log2Ceil(numRegs).W))
      val rregVal1 = Output(UInt(32.W))
      val rregVal2 = Output(UInt(32.W))
      
      val wEnable  = Input(new ctrlRegFileWbEnable)
      val wregIdx  = Input(UInt(log2Ceil(numRegs).W))
      val wregVal  = Input(UInt(32.W))
      
    // Test interface  
    val testRdIdx : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testRdVal : Option[UInt]  = if(enableTestInit)  Some(Output(UInt(32.W))) else None


    val testReadRegs = if (enableTestInit) Some(Output(Vec(16, UInt(32.W)))) else None

   })


  
    val regFile = Reg(Vec(numRegs,UInt(32.W)))

    when( io.wEnable.en === true.B && io.wregIdx =/= 0.U) {
       regFile(io.wregIdx) := io.wregVal
    }

    io.rregVal1 := Mux(io.rregIdx1 === 0.U, 0.U, regFile(io.rregIdx1)) 
    io.rregVal2 := Mux(io.rregIdx2 === 0.U, 0.U, regFile(io.rregIdx2)) 

    if(enableTestInit) io.testRdVal.get := regFile(io.testRdIdx.get)

    if (enableTestInit) {
      for (i <- 0 until 16) {
         io.testReadRegs.get(i) := regFile(i)
      }
  }
}
