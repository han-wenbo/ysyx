package core.control
import chisel3._
import chisel3.util._
import core.control._
import chisel3.util.experimental.decode._
import chisel3.ChiselEnum
import chisel3.util.BitPat

object InstDecode {

object AluOp extends ChiselEnum {
  val add = Value(0.U)
}
case class RV32IPattern(
  bitPat:   BitPat,   
  regWrEn:  Boolean,
  aluSel :  Boolean,
  aluOp:   AluOp.Type, 
  memR:     Boolean,
  regWbSel: Boolean
) extends DecodePattern


  val __ADDI =  BitPat("b????????????_?????_000_?????_0010011")

  val __ADD  =  BitPat("b0000000_?????_?????_000_?????_01100_11")

  val addi = RV32IPattern(__ADDI,true,false,AluOp.add,false,false)





  object AluOpField extends DecodeField[RV32IPattern, UInt] {
     def name = "alu operation"
     def chiselType: UInt = UInt(3.W) // 你定义的 AluOp 的宽度
     def genTable(p: RV32IPattern): BitPat = p.aluOp match {
         case AluOp.add => BitPat("b000")
         }
     }

  object regWrEn extends BoolDecodeField[RV32IPattern] {
    def name = "reg wb enable"
    def genTable(p: RV32IPattern) = if (p.regWrEn) y else n
  }

  object aluSel extends BoolDecodeField[RV32IPattern] {
    def name = "alu sel"
    def genTable(p: RV32IPattern) = if (p.aluSel) y else n
  }

  object memR extends BoolDecodeField[RV32IPattern] {
    def name = "memR"
    def genTable(p: RV32IPattern) = if (p.memR) y else n
  }

  object regWbSel extends BoolDecodeField[RV32IPattern] {
    def name = "regWbSell"
    def genTable(p: RV32IPattern) = if (p.regWbSel) y else n
  }
  
  val patterns = Seq(addi)
  val fields   = Seq(regWrEn,aluSel,AluOpField,memR,regWbSel)

  val decodeTbl = new DecodeTable(patterns, fields)


    

}
