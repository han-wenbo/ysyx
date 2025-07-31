package core.control
import chisel3._
import chisel3.util._
import core.control._
import chisel3.util.experimental.decode._
import chisel3.ChiselEnum
import chisel3.util.BitPat

object ALUOP extends ChiselEnum {
    val ADD,SUB,NOT,AND,
        OR ,XOR,SLT,ULT,
        SLL,SLR,SAR,EQU
        = Value
}

object InstDecode {
  
  val Y = true
  val N = false
  val IS_JMP_INST = true
  val NOT_JMP_INST = false
  val IS_BRH_INST = true
  val NOT_BRH_INST = false

  val ALUSRC1_FROM_PC  = BitPat("b00")  // for branch and jmp to calculate address 
  val ALUSRC1_FROM_REG = BitPat("b01") 
  val ALUSRC1_FROM_X0  = BitPat("b10") // for lui 

  val ALUSRC2_FROM_REG = true
  val ALUSRC2_FROM_IMM = false
  val REGWBSRC_FROM_MEM = BitPat("b01")
  val REGWBSRC_FROM_ALU = BitPat("b00")
  val REGWBSRC_FROM_PC4 = BitPat("b10")

  val MEMWR_1 =  BitPat("b0001")
  val MEMWR_2 =  BitPat("b0011")
  val MEMWR_4 =  BitPat("b1111")
  val MEMWR_X =  BitPat("b0000")
  
  val REGWBSRC_DC       = BitPat("b00")

  val LB_INST  = BitPat("b000")
  val LH_INST  = BitPat("b001")
  val LW_INST  = BitPat("b010")
  val LBU_INST = BitPat("b100")
  val LHU_INST = BitPat("b110")
  val NOT_LOAD = BitPat("b011")

  case class RV32IPattern(
    bitPat:           BitPat,   
    regFileWbEnable:  Boolean,
    aluSrc1Sel :      BitPat,
    aluSrc2Sel :      Boolean,
    aluOp:            ALUOP.Type, 
    branchInst:       Boolean,
    jmpInst:          Boolean,
    memRead:          Boolean,
    regWbValExtSel:   BitPat,
    regWbSrcSel:      BitPat,
    
    memWrEn    :      Boolean,
    memWrMask  :      BitPat
  ) extends DecodePattern



 /* val __ADD  =  BitPat("b0000000_?????_?????_000_?????_01100_11")
  val __ADDI =  BitPat("b????????????_?????_000_?????_0010011")

  val __LW   = BitPat("b???????_?????_?????_010_?????_00000_11")
  val __SW   =  BitPat("b???????_?????_?????_010_?????_01000_11")

  val __BEQ  =   BitPat("b???????_?????_?????_000_?????_11000_11")

  val __AUIPC  =  BitPat("b???????_?????_?????_???_?????_00101_11")
  val __JAL  =  BitPat("b???????_?????_?????_???_?????_11011_11")
  val __JALR  =  BitPat("b???????_?????_?????_000_?????_11001_11") */
val __ADD = BitPat("b0000000_?????_?????_000_?????_01100_11")
val __SLT = BitPat("b0000000_?????_?????_010_?????_01100_11")
val __SLTU = BitPat("b0000000_?????_?????_011_?????_01100_11")
val __XOR = BitPat("b0000000_?????_?????_100_?????_01100_11")
val __OR = BitPat("b0000000_?????_?????_110_?????_01100_11")
val __AND = BitPat("b0000000_?????_?????_111_?????_01100_11")
val __SUB = BitPat("b0100000_?????_?????_000_?????_01100_11")
val __SLL = BitPat("b0000000_?????_?????_001_?????_01100_11")
val __SLR = BitPat("b0000000_?????_?????_101_?????_01100_11")

val __SRA = BitPat("b0100000_?????_?????_101_?????_01100_11")
val __JAL = BitPat("b???????_?????_?????_???_?????_11011_11")
val __JALR = BitPat("b???????_?????_?????_000_?????_11001_11")
val __ADDI = BitPat("b???????_?????_?????_000_?????_00100_11")
val __XORI = BitPat("b???????_?????_?????_100_?????_00100_11")
val __ORI = BitPat("b???????_?????_?????_110_?????_00100_11")
val __ANDI = BitPat("b???????_?????_?????_111_?????_00100_11")
val __SLTI = BitPat("b???????_?????_?????_010_?????_00100_11")
val __SLTIU = BitPat("b???????_?????_?????_011_?????_00100_11")
val __LB = BitPat("b???????_?????_?????_000_?????_00000_11")
val __LH = BitPat("b???????_?????_?????_001_?????_00000_11")
val __LW = BitPat("b???????_?????_?????_010_?????_00000_11")
val __LBU = BitPat("b???????_?????_?????_100_?????_00000_11")
val __LHU = BitPat("b???????_?????_?????_101_?????_00000_11")
val __SLLI = BitPat("b0000000_?????_?????_001_?????_00100_11")
val __SRLI = BitPat("b0000000_?????_?????_101_?????_00100_11")
val __SRAI = BitPat("b0100000_?????_?????_101_?????_00100_11")
val __SB = BitPat("b???????_?????_?????_000_?????_01000_11")
val __SW = BitPat("b???????_?????_?????_010_?????_01000_11")
val __SH = BitPat("b???????_?????_?????_001_?????_01000_11")
val __BEQ = BitPat("b???????_?????_?????_000_?????_11000_11")
val __BNE = BitPat("b???????_?????_?????_001_?????_11000_11")
val __BLT = BitPat("b???????_?????_?????_100_?????_11000_11")
val __BGE = BitPat("b???????_?????_?????_101_?????_11000_11")
val __BLTU = BitPat("b???????_?????_?????_110_?????_11000_11")
val __BGEU = BitPat("b???????_?????_?????_111_?????_11000_11")
val __MUL = BitPat("b0000001_?????_?????_000_?????_01100_11")
val __MULH = BitPat("b0000001_?????_?????_001_?????_01100_11")
val __MULU = BitPat("b0000001_?????_?????_011_?????_01100_11")
val __DIV = BitPat("b0000001_?????_?????_100_?????_01100_11")
val __DIVU = BitPat("b0000001_?????_?????_101_?????_01100_11")
val __REM = BitPat("b0000001_?????_?????_110_?????_01100_11")
val __REMU = BitPat("b0000001_?????_?????_111_?????_01100_11")
val __AUIPC = BitPat("b???????_?????_?????_???_?????_00101_11")
val __LUI = BitPat("b???????_?????_?????_???_?????_01101_11")


  

  val ADD   =   RV32IPattern(__ADD   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLT   =   RV32IPattern(__SLT   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.SLT,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLTU   =   RV32IPattern(__SLTU   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.ULT,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val XOR   =   RV32IPattern(__XOR   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.XOR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val OR   =   RV32IPattern(__OR   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.OR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val AND   =   RV32IPattern(__AND   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.AND,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SUB   =   RV32IPattern(__SUB   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.SUB,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLL   =   RV32IPattern(__SLL   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.SLL,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLR   =   RV32IPattern(__SLR   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.SLR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SRA   =   RV32IPattern(__SRA   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_REG, ALUOP.SAR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  

  val JAL  =   RV32IPattern(__JAL ,Y, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,IS_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_PC4,N,MEMWR_X )
  val JALR  =   RV32IPattern(__JALR ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,IS_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_PC4,N,MEMWR_X )


  val ADDI   =   RV32IPattern(__ADDI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val XORI   =   RV32IPattern(__XORI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.XOR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val ORI   =   RV32IPattern(__ORI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.OR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val ANDI   =   RV32IPattern(__ANDI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.AND,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLTI   =   RV32IPattern(__SLTI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.SLT,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLTIU   =   RV32IPattern(__SLTIU   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ULT,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SLLI   =   RV32IPattern(__SLLI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.SLL,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SRLI   =   RV32IPattern(__SRLI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.SLR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val SRAI   =   RV32IPattern(__SRAI   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.SAR,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )

  val LB   =   RV32IPattern(__LB   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, LB_INST, REGWBSRC_FROM_MEM, N,MEMWR_X )
  val LH   =   RV32IPattern(__LH   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, LH_INST, REGWBSRC_FROM_MEM, N,MEMWR_X )
  val LW   =   RV32IPattern(__LW   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, LW_INST, REGWBSRC_FROM_MEM, N,MEMWR_X )
  val LBU   =   RV32IPattern(__LBU   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, LBU_INST, REGWBSRC_FROM_MEM, N,MEMWR_X )
  val LHU   =   RV32IPattern(__LHU   ,Y, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, LHU_INST, REGWBSRC_FROM_MEM, N,MEMWR_X )


  val SB   =   RV32IPattern(__SB   ,N, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, NOT_LOAD,REGWBSRC_FROM_ALU, Y,MEMWR_1 )
  val SH   =   RV32IPattern(__SH   ,N, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, NOT_LOAD,REGWBSRC_FROM_ALU, Y,MEMWR_2 )
  val SW   =   RV32IPattern(__SW   ,N, ALUSRC1_FROM_REG, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, Y, NOT_LOAD,REGWBSRC_FROM_ALU, Y,MEMWR_4 )

  val BEQ  =   RV32IPattern(__BEQ ,N, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD, IS_BRH_INST,NOT_JMP_INST, N, NOT_LOAD, REGWBSRC_DC,N,MEMWR_X )
  val BNE  =   RV32IPattern(__BNE ,N, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD, IS_BRH_INST,NOT_JMP_INST, N, NOT_LOAD, REGWBSRC_DC,N,MEMWR_X )
  val BLT  =   RV32IPattern(__BLT ,N, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD, IS_BRH_INST,NOT_JMP_INST, N, NOT_LOAD, REGWBSRC_DC,N,MEMWR_X )
  val BGE  =   RV32IPattern(__BGE ,N, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD, IS_BRH_INST,NOT_JMP_INST, N, NOT_LOAD, REGWBSRC_DC,N,MEMWR_X )
  val BLTU  =   RV32IPattern(__BLTU ,N, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD, IS_BRH_INST,NOT_JMP_INST, N, NOT_LOAD, REGWBSRC_DC,N,MEMWR_X )
  val BGEU  =   RV32IPattern(__BGEU ,N, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD, IS_BRH_INST,NOT_JMP_INST, N, NOT_LOAD, REGWBSRC_DC,N,MEMWR_X )

  val LUI =   RV32IPattern(__LUI ,Y, ALUSRC1_FROM_X0, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
  val AUIPC =   RV32IPattern(__AUIPC ,Y, ALUSRC1_FROM_PC, ALUSRC2_FROM_IMM, ALUOP.ADD,NOT_BRH_INST,NOT_JMP_INST, N, NOT_LOAD,REGWBSRC_FROM_ALU,N,MEMWR_X )
   object RegWbValExtSelObj extends DecodeField[RV32IPattern, UInt] {
     def name = "reg wb val ext sel boj"
     def chiselType: UInt = UInt(3.W) 
     def genTable(p: RV32IPattern): BitPat = p.regWbValExtSel
     }

 
  object MemWrMaskObj extends DecodeField[RV32IPattern, UInt] {
     def name = "mask"
     def chiselType: UInt = UInt(4.W) 
     def genTable(p: RV32IPattern): BitPat = p.memWrMask
     }

 object MemWrEnObj extends BoolDecodeField[RV32IPattern] {
    def name = "mem wr en obj"
    def genTable(p: RV32IPattern) = if (p.memWrEn) y else n
  }

 /*  object ALUOP extends ChiselEnum {
    val ADD,SUB,NOT,AND,
        OR ,XOR,SLT,ULT,
        SLL,SLR,SAR,EQU
*/ 
  object AluOpFieldObj extends DecodeField[RV32IPattern, UInt] {
     def name = "alu operation"
     def chiselType: UInt = UInt(4.W) // 你定义的 AluOp 的宽度
     def genTable(p: RV32IPattern): BitPat =  p.aluOp match {
       case ALUOP.ADD => BitPat("b0000")
       case ALUOP.SUB => BitPat("b0001")
       case ALUOP.NOT => BitPat("b0010")
       case ALUOP.AND => BitPat("b0011")
       case ALUOP.OR  => BitPat("b0100")
       case ALUOP.XOR => BitPat("b0101")
       case ALUOP.SLT => BitPat("b0110")
       case ALUOP.ULT => BitPat("b0111")
       case ALUOP.SLL => BitPat("b1000")
       case ALUOP.SLR => BitPat("b1001")
       case ALUOP.SAR => BitPat("b1010")
       case ALUOP.EQU => BitPat("b1011")
     }
     }

 object JmpInstObj extends BoolDecodeField[RV32IPattern] {
    def name = "name:jmpInst"
    def genTable(p: RV32IPattern) = if (p.jmpInst) y else n
  }
object BranchInstObj extends BoolDecodeField[RV32IPattern] {
    def name = "name:BranchInst"
    def genTable(p: RV32IPattern) = if (p.branchInst) y else n
  }

  object RegFileWbEnableObj extends BoolDecodeField[RV32IPattern] {
    def name = "reg wb enable"
    def genTable(p: RV32IPattern) = if (p.regFileWbEnable) y else n
  }

 object AluSrc1SelObj extends DecodeField[RV32IPattern, UInt] {
    def name = "alu1 sel"
     def chiselType: UInt = UInt(2.W) 
    def genTable(p: RV32IPattern) = p.aluSrc1Sel
  }

  object AluSrc2SelObj extends BoolDecodeField[RV32IPattern] {
    def name = "alu sel"
    def genTable(p: RV32IPattern) = if (p.aluSrc2Sel) y else n
  }

  object MemReadObj extends BoolDecodeField[RV32IPattern] {
    def name = "memR"
    def genTable(p: RV32IPattern) = if (p.memRead) y else n
  }

  object RegWbSrcSelObj extends DecodeField[RV32IPattern, UInt] {
     def name = "Reg write back Sel"
     def chiselType: UInt = UInt(2.W) 
     def genTable(p: RV32IPattern): BitPat = p.regWbSrcSel
     }


  val fields   = Seq(AluOpFieldObj, RegWbSrcSelObj, RegFileWbEnableObj, MemReadObj,AluSrc2SelObj,AluSrc1SelObj,JmpInstObj, BranchInstObj,MemWrMaskObj, MemWrEnObj,RegWbValExtSelObj)
  val patterns = Seq(ADD, SLT, SLTU, XOR, OR, AND, SUB, SLL, SLR, JAL, JALR, ADDI, XORI, ORI, ANDI, SLTI, SLTIU, LB, LH, LW, LBU, LHU, SLLI, SRLI, SRAI, SB, SW, SH, BEQ, BNE, BLT, BGE, BLTU, BGEU, AUIPC, LUI, SRA)
  val decodeTbl = new DecodeTable(patterns, fields)
}
