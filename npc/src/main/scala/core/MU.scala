package core
import chisel3._
import core.control._
import chisel3.util._

class MU extends Module {
  val io = IO(new Bundle {

    val fromEXU    = Flipped(new EXUtoMU)
     
    val exuCtrl    = Input(new EXUCtrl)

    val muCtrl     = Output(new MUCtrl)
    val memWbVal   = Output(UInt(32.W))
    val aluWbVal   = Output(UInt(32.W))
    val snpcWbVal  = Output(UInt(32.W))

    // Pass to FU, and these signals will not be stored into pipeline registers.
    val aluPc = Output(UInt(32.W))
    val pcSrcSel = Output(Bool())
    
  })

  val memContrl = Module(new MemContrl)

  memContrl.io.clk := clock
  io.snpcWbVal := io.fromEXU.snpc

  io.aluWbVal := io.fromEXU.aluResult

// Control signals were passed to WRU
  io.muCtrl.RegWbSrcSel.regWbSrcSel := io.exuCtrl.RegWbSrcSel.regWbSrcSel 
  io.muCtrl.RegWbValExtSel.regWbValExtSel := io.exuCtrl.RegWbValExtSel.regWbValExtSel 
// Control signals and Data were passed to FU
  io.aluPc := io.fromEXU.aluResult

  val needJmp = io.exuCtrl.JmpInst.jmpInst  || io.fromEXU.branchTrue
  io.pcSrcSel := Mux(needJmp, true.B, false.B)


// Read port 
  memContrl.io.valid := io.exuCtrl.MemRead.memRead
  memContrl.io.raddr := io.fromEXU.aluResult
   // io.fromEXU.aluResult 

  io.memWbVal := memContrl.io.rdata

// Write port
  memContrl.io.wen := io.exuCtrl.MemWrEn.memWrEn
  memContrl.io.wdata := io.fromEXU.rs2Val 
  memContrl.io.waddr := io.fromEXU.aluResult
  memContrl.io.wmask := io.exuCtrl.MemWrMask.memWrMask

}


class MemContrl  extends BlackBox with HasBlackBoxResource {
  val io = IO(new Bundle{ 
     val clk   = Input(Clock())
     val valid = Input(Bool())
     val raddr = Input(UInt(32.W))
     val wen   = Input(Bool())
     val waddr = Input(UInt(32.W))
     val wdata = Input(UInt(32.W))
     val wmask = Input(UInt( 8.W))
     
     val rdata= Output(UInt(32.W))
  })

  addResource("/DpiMem.sv") 
}
