package core
import chisel3._
import chisel3.util._
import core.control._
import chisel3.util.experimental.decode._
import chisel3.ChiselEnum
import chisel3.util.BitPat
import core.control.InstDecode._

class DU (enableTestInit : Boolean = false) extends Module {
  val io = IO(new Bundle {
    val inst         = Input(UInt(32.W))
    val ctrl         = Output(new DUCtrl)
    val aluSrc1      = Output(UInt(32.W))
    val aluSrc2      = Output(UInt(32.W))
   // val regWrIdxOut  = Output(UInt(4.W))

    val regWrBackVal = Input(UInt(32.W))
    //val regWrbackEn  = Input(new ctrlRegFileEnable)  
    //val regWrIdx     = Input(UInt(4.W))     
    /* for unit test */
    val testEn    : Option[Bool]  = if(enableTestInit)  Some(Input(Bool())) else None 
    val testIdx   : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testVal   : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(32.W))) else None
    
    val testRdIdx : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testRdVal : Option[UInt]  = if(enableTestInit)  Some(Output(UInt(32.W))) else None

  }) 
 val op      = io.inst(6,0)
 val rd      = io.inst(11,7)
 val rs1     = io.inst(19,15)
 val rs2     = io.inst(24,20)
 val func7   = io.inst(11,7)
 val func3   = io.inst(14,12) 
 val imm     = io.inst(31,20)

  val instDecoder = Module(new InstDecoder)
  val regFile     = Module(new RegFile(enableTestInit,16))
  instDecoder.io.inst := io.inst
 
  // register file inputs 
  regFile.io.rregIdx1 := rs1
  regFile.io.rregIdx2 := rs2


  //val wEnable  =  if(enableTestInit) io.testEn.getOrElse(false.B) || io.regWrbackEn.en else io.regWrbackEn.en 
  val wEnable  =  if(enableTestInit) io.testEn.getOrElse(false.B) ||  instDecoder.io.ctrl.RegFileEnable.en else  instDecoder.io.ctrl.RegFileEnable.en
  //val wregIdx  =  if(enableTestInit) Mux( io.testEn.getOrElse(false.B), io.testIdx.getOrElse(0.U), io.regWrIdx) else io.regWrIdx 
  val wregIdx  =  if(enableTestInit) Mux( io.testEn.getOrElse(false.B), io.testIdx.getOrElse(0.U), rd) else rd 
  val wregVal  =  if(enableTestInit) Mux( io.testEn.getOrElse(false.B), io.testVal.getOrElse(0.U), io.regWrBackVal) else io.regWrBackVal 
  regFile.io.wEnable.en  := wEnable 
  regFile.io.wregIdx  := wregIdx 
  regFile.io.wregVal  := wregVal 

  // DU's outputs
  io.aluSrc1 := regFile.io.rregVal1
  io.aluSrc2 := Mux(instDecoder.io.ctrl.AluSrc2Sel.muxSel, regFile.io.rregVal2, imm) 
 // io.regWrIdxOut := rd

  io.ctrl.AluOp.op := instDecoder.io.ctrl.AluOp.op 
  io.ctrl.MemRead.memRead := instDecoder.io.ctrl.MemRead.memRead 
  io.ctrl.RegWbSrcSel.regWbSrcSel := instDecoder.io.ctrl.RegWbSrcSel.regWbSrcSel
  //io.ctrl.RegFileEnable.en := instDecoder.io.ctrl.RegFileEnable.en
 
  if(enableTestInit) regFile.io.testRdIdx.get := io.testRdIdx.get
  if(enableTestInit) io.testRdVal.get := regFile.io.testRdVal.get
}


class InstDecoder extends Module {
   val io = IO(new Bundle{ 
      val inst = Input(UInt(32.W))
      val ctrl = Output(new allCtrl)
   })
  
  val result = decodeTbl.decode(io.inst)  

  io.ctrl.RegFileEnable.en := result(regWrEn).asBool
  io.ctrl.AluSrc2Sel.muxSel := result(aluSel).asBool
  io.ctrl.AluOp.op := result(AluOpField) 
  io.ctrl.MemRead.memRead :=  result(memR).asBool
  io.ctrl.RegWbSrcSel.regWbSrcSel := result(regWbSel).asBool

}
/*
class SimExitBlackBox extends BlackBox with HasBlackBoxResource {
   val io = IO(new Bundle { 
      val triSg = Input(Bool())
   })

   addResource("/DpiExit.sv")
}
*/
