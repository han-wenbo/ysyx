package core.control
import chisel3._



class ctrlRegFileWbEnable extends Bundle {
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
class ctrlMemRead extends Bundle {
  val memRead  = Bool()
}
// 00: alu result as write back value
// 01: memory value as 
// 10: pc + 4
class ctrlRegWbSrcSel extends Bundle { val regWbSrcSel = UInt(2.W)
}
class ctrlAluSrc1Sel extends Bundle {
   val aluSrc1Sel = UInt(2.W)
}
// 0: pc + 4
// 1: from ALU
class ctrlJmpInst extends Bundle {
  val jmpInst = Bool()
}
class ctrlBranchInst extends Bundle{
  val branchInst = Bool()
}
class ctrlMemWrMask extends Bundle{
  val memWrMask = UInt(4.W)
}
class ctrlMemWrEn extends Bundle{
  val memWrEn = Bool()
}
class ctrlMemWbValExtSel extends Bundle{
  val regWbValExtSel = UInt(3.W)
}

// CSR
class ctrlCsrWbEnable extends Bundle {
  val csrWbEnable = Bool()
}
// Exception
class ctrlTrapInst extends Bundle {
  val trapInst = Bool()
}

class ctrlToMepc extends Bundle {
  val toMepc = Bool()
}
// All signals which were yeilded by Instrcution Decoder
class allCtrl extends Bundle {
   val AluSrc2Sel    = new ctrlAluSrc2Sel
   val AluSrc1Sel    = new ctrlAluSrc1Sel
   val AluOp	     = new ctrlAluOp 
   val MemRead       = new ctrlMemRead
 
   
   val RegFileWbEnable = new ctrlRegFileWbEnable
   val RegWbValExtSel   = new ctrlMemWbValExtSel

   val RegWbSrcSel   = new ctrlRegWbSrcSel

   val JmpInst       = new ctrlJmpInst
   val BranchInst    = new ctrlBranchInst
     
   val MemWrMask     = new ctrlMemWrMask 
   val MemWrEn       = new ctrlMemWrEn 

   val CsrWbEnable   = new ctrlCsrWbEnable 
   val TrapInst     = new ctrlTrapInst
   val ToMepc       = new ctrlToMepc
}

// control signals that DU passes to next module
class DUCtrl extends Bundle {
   val AluOp	     = new ctrlAluOp 
   val MemRead       = new ctrlMemRead
   val RegWbSrcSel   = new ctrlRegWbSrcSel
   val RegWbValExtSel   = new ctrlMemWbValExtSel
   val JmpInst       = new ctrlJmpInst
   val BranchInst    = new ctrlBranchInst

   val MemWrMask     = new ctrlMemWrMask 
   val MemWrEn       = new ctrlMemWrEn 

   //val RegFileWbEnable = new ctrlRegFileWbEnable
}

class DU2FUCtrl extends Bundle {
   val TrapInst     = new ctrlTrapInst
   val ToMepc       = new ctrlToMepc
}

class EXUCtrl extends Bundle {
  // val RegFileWbEnable = new ctrlRegFileWbEnable
   val MemRead       = new ctrlMemRead
   val RegWbSrcSel   = new ctrlRegWbSrcSel
   val RegWbValExtSel   = new ctrlMemWbValExtSel
   val JmpInst       = new ctrlJmpInst
  
   val MemWrMask     = new ctrlMemWrMask 
   val MemWrEn       = new ctrlMemWrEn 

   // Sigals which were not yeilded by Decoder

} 
class MUCtrl extends Bundle {
   // 0: alu result as write back value
   val RegWbSrcSel   = new ctrlRegWbSrcSel
   val RegWbValExtSel   = new ctrlMemWbValExtSel
}

