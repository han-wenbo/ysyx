package core
import chisel3._
import core.control._
import chisel3.util._

class WBU (regNums : Int) extends Module {
   val io = IO(new Bundle {
     //val exuCtrlIn   = Input(new EXUCtrl)
     //val needWB      = Output(new EXUCtrl)

     //val regWrIdxIn     = Input(UInt(log2Ceil(regNums).W))
     //val regWrIdxOut    = Output(UInt(log2Ceil(regNums).W))

     val wrValIn        = Input(UInt(32.W)) 
     val wrValOut       = Output(UInt(32.W)) 
 })
  //io.needWB.RegFileEnable.en := io.exuCtrlIn.RegFileEnable.en
 // io.regWrIdxOut             := io.regWrIdxIn
  io.wrValOut                := io.wrValIn
 
}
