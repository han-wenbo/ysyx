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

     val muCtrl          = Input(new MUCtrl)
     val memWbVal        = Input(UInt(32.W)) 
     val aluWbVal        = Input(UInt(32.W)) 
     val snpcWbVal          = Input(UInt(32.W))
     val wbValOut       = Output(UInt(32.W)) 
 })
  //io.needWB.RegFileWbEnable.en := io.exuCtrlIn.RegFileWbEnable.en
 // io.regWrIdxOut             := io.regWrIdxIn
 
  val regWbValExt = Module(new MemWbValExt)
  regWbValExt.io.v   := io.memWbVal 
  regWbValExt.io.sel := io.muCtrl.RegWbValExtSel.regWbValExtSel


  io.wbValOut                := MuxLookup(io.muCtrl.RegWbSrcSel.regWbSrcSel, 0.U) (Seq(
         "b00".U -> io.aluWbVal,
         "b01".U -> regWbValExt.io.output,
         "b10".U -> io.snpcWbVal
       ))

}

class MemWbValExt extends Module {
   val io = IO(new Bundle{  
     val v      = Input(UInt(32.W))
     val sel    = Input(UInt(3.W))

     val output = Output(UInt(32.W))
   })
 val lbExt  = Fill(24, io.v(7)) ## io.v(7,0) 
 val lhExt  = Fill(16, io.v(15)) ## io.v(15,0) 
 val lwExt  = io.v
 val lbuExt = Fill(24, 0.U) ## io.v(7,0) 
 val lhuExt = Fill(16, 0.U) ## io.v(15,0) 
 
 io.output := MuxLookup(io.sel, 2.U) (Seq(
   "b000".U -> lbExt,
   "b001".U -> lhExt,
   "b010".U -> lwExt,
   "b100".U -> lbuExt,
   "b110".U -> lhuExt
  ))
}
