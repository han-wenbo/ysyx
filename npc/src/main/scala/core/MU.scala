package core
import chisel3._
import core.control._
import chisel3.util._

class MU extends Module {
  val io = IO(new Bundle {
    val aluResult  = Input(UInt(32.W))
    val exuCtrl    = Input(new EXUCtrl)
    val muCtrl     = Output(new MUCtrl)
    val memWbVal   = Output(UInt(32.W))
    val aluWbVal   = Output(UInt(32.W))
  })

  val memContrl = Module(new MemContrl)

  io.aluWbVal := io.aluResult

// Control signals output
  io.muCtrl.RegWbSrcSel.regWbSrcSel := io.exuCtrl.RegWbSrcSel.regWbSrcSel 

// Read port 
  memContrl.io.valid := io.exuCtrl.MemRead.memRead 
  memContrl.io.raddr := io.aluResult 

  io.memWbVal := memContrl.io.rdata

// Write port
  memContrl.io.wen := false.B
  memContrl.io.wdata := 0.U
  memContrl.io.waddr := 0.U
  memContrl.io.wmask := 0.U
}


class MemContrl  extends BlackBox with HasBlackBoxResource {
  val io = IO(new Bundle{ 
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
