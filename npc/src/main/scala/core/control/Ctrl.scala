package core.control
import chisel3._


class ctrlRegFileEnable extends Bundle {
  val en = Bool()
}

// 0: imm
// 1: regvalue
class ctrlAluSrc2Sel extends Bundle {
   val muxSel = Bool()
}

class ctrlAluOp extends Bundle {
  val op = UInt(4.W)
}
class ctrlAluImmExt extends Bundle {
  val isExt = Bool()
}

class allCtrl extends Bundle {
   val RegFileEnable = new ctrlRegFileEnable
   val AluSrc2Sel    = new ctrlAluSrc2Sel
   val AluOp	     = new ctrlAluOp 
}

// control signals that DU passes to next module
class DUCtrl extends Bundle {
   val AluOp	     = new ctrlAluOp 
   //val RegFileEnable = new ctrlRegFileEnable
}

class EXUCtrl extends Bundle {
   val RegFileEnable = new ctrlRegFileEnable
} 
