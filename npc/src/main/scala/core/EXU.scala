package core
import chisel3._
import core.control._
import chisel3.util._ 
import _root_.circt.stage.ChiselStage

class ALUDataIO extends Bundle {
    val a     = Input(UInt(32.W))
    val b     = Input(UInt(32.W))
    val out   = Output(UInt(32.W))
}
class ALUFlagsIO extends Bundle {
    val zero  = Output(UInt(1.W))
    val cflag = Output(UInt(1.W))
    val oflag = Output(UInt(1.W))
}
class ALUIO extends Bundle {
  val aluData        = new ALUDataIO 
  val aluFlags       = new ALUFlagsIO
  val op             = Input(UInt(4.W))
}

class _CmperIO extends Bundle {
    val src1 = Input(UInt(32.W))
    val src2 = Input(UInt(32.W))
    // decide whether branchT is true using @bInstFun3
    val bInstFunc3 = Input(UInt(3.W))
    val branchTrue = Output(Bool())
}
class CmperIO extends Bundle{
    val cmperIO      = new _CmperIO
    val isBranchInst = Input(Bool())
}


class EXU (regNums:Int) extends Module {
  val io = IO(new Bundle{ 
    val fromDU = Flipped(new DUtoEXUIO)
    val toMU  =  new EXUtoMU 
    val duCtrl           = Input(new DUCtrl)
    val exuCtrl          = Output(new EXUCtrl)

  })
  val alu = Module(new ALU)
 
  // snpc will be passed to WB, and then write back to register when executing a JAL
  io.toMU.snpc := io.fromDU.snpc
  io.toMU.rs2Val := io.fromDU.rs2Val
  
  io.exuCtrl.JmpInst.jmpInst := io.duCtrl.JmpInst.jmpInst
  io.exuCtrl.MemRead.memRead  := io.duCtrl.MemRead.memRead
  io.exuCtrl.RegWbSrcSel.regWbSrcSel := io.duCtrl.RegWbSrcSel.regWbSrcSel
  io.exuCtrl.MemWrEn.memWrEn := io.duCtrl.MemWrEn.memWrEn
  io.exuCtrl.MemWrMask.memWrMask := io.duCtrl.MemWrMask.memWrMask
  io.exuCtrl.RegWbValExtSel.regWbValExtSel := io.duCtrl.RegWbValExtSel.regWbValExtSel

  alu.io.op                := io.duCtrl.AluOp.op
  alu.io.aluData.a         := io.fromDU.aluSrc1
  alu.io.aluData.b         := io.fromDU.aluSrc2
  io.toMU.aluResult        := alu.io.aluData.out
  //io.exuCtrl.RegFileWbEnable.en := io.duCtrl.RegFileWbEnable.en
 // io.regWrIdxOut           := io.regWrIdxIn
 
  val cmper = Module(new Cmper) 
  cmper.io.cmperIO.src1 := io.fromDU.cmperSrc1
  cmper.io.cmperIO.src2 := io.fromDU.cmperSrc2
  cmper.io.cmperIO.bInstFunc3 := io.fromDU.bInstFunc3
  io.toMU.branchTrue := cmper.io.cmperIO.branchTrue

  cmper.io.isBranchInst := io.duCtrl.BranchInst.branchInst
}



class Cmper extends Module {
  val io = IO(new CmperIO)

   val BEQ = 0.U
   val BNE = 1.U
   val BLT = 4.U
   val BGE = 5.U
   val BLTU = 6.U
   val BGEU = 7.U

    val equal =  io.cmperIO.src1 === io.cmperIO.src2
    val uge   =  io.cmperIO.src1 > io.cmperIO.src2 
    val sge   =  io.cmperIO.src1.asSInt > io.cmperIO.src2.asSInt

    val _branchTrue = MuxLookup(io.cmperIO.bInstFunc3, false.B) (
      Seq(
        BEQ ->  equal,
        BNE -> !equal,
        BLT -> (!sge && !equal)  ,
        BGE ->  (sge || equal),
        BLTU->  (!uge && !equal) ,
        BGEU->  (uge || equal)
        )) 

    io.cmperIO.branchTrue := _branchTrue & io.isBranchInst
}


class ALU extends Module {
  val io = IO(new ALUIO)

  val a5 = 0.U(1.W) ## io.aluData.a
  val b5 = 0.U(1.W) ## io.aluData.b
  val inverse_bb  =  ~io.aluData.b
  val inverse_b   =  (inverse_bb + 1.U(32.W))(31,0) 
  val inverse_b5 =  0.U(1.W) ## inverse_b

  // Default value
  io.aluFlags.cflag  :=  0.U(1.W)
  io.aluFlags.oflag  :=  0.U(1.W)
  io.aluData.out    :=  "hFFFFFFFF".U(32.W)
  io.aluFlags.zero	:= !(io.aluData.out.orR)
  switch(io.op) {

    is(ALUOP.ADD.asUInt) {
      val out_temp = a5 + b5
      io.aluData.out	:= out_temp(31,0)
      io.aluFlags.cflag	:= out_temp(32)
      io.aluFlags.oflag	:= ((a5(31) && b5(31)) && ~out_temp(31)) || ((~a5(31) && ~b5(31)) && out_temp(31)) 
    }
    is(ALUOP.SUB.asUInt) {
      val out_temp1 = a5 + inverse_b5
      io.aluData.out	:= out_temp1(31,0)
      io.aluFlags.cflag	:= !out_temp1(32)
      io.aluFlags.oflag	:= ((~a5(31) && b5(31)) && out_temp1(31)) || ((a5(31) && ~b5(31)) && ~out_temp1(31)) 
    }
    is(ALUOP.NOT.asUInt) {
      io.aluData.out	:= ~io.aluData.a
    }
    is(ALUOP.AND.asUInt) {
      io.aluData.out	:= io.aluData.a & io.aluData.b
    }
    is(ALUOP.OR.asUInt) {
      io.aluData.out	:= io.aluData.a | io.aluData.b
    }
    is(ALUOP.XOR.asUInt) {
      io.aluData.out	:= io.aluData.a ^ io.aluData.b
    }
    is(ALUOP.SLT.asUInt) {
      io.aluData.out	:= io.aluData.a.asSInt < io.aluData.b.asSInt
    }
    is(ALUOP.ULT.asUInt) {
      io.aluData.out    := io.aluData.a  < io.aluData.b
    }
    is(ALUOP.SLL.asUInt) {
      io.aluData.out    := io.aluData.a << io.aluData.b(4,0)
    }
    is(ALUOP.SLR.asUInt) {
      io.aluData.out    := io.aluData.a >> io.aluData.b(4,0)
    }
    is(ALUOP.SAR.asUInt) {
      io.aluData.out    := (io.aluData.a.asSInt >> io.aluData.b(4,0)).asUInt
    }
    is(ALUOP.EQU.asUInt) {
      io.aluData.out	:= (io.aluData.a === io.aluData.b).asUInt
    }
  }
}

object GenEXU extends App {
  ChiselStage.emitSystemVerilogFile(
    new EXU(16),
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info", "-default-layer-specialization=enable")
  )
}

