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

class EXUIO (regNums : Int) extends Bundle {
  val aluData        = new ALUDataIO 
  val duCtrl           = Input(new DUCtrl)
 // val exuCtrl        = Output(new EXUCtrl)
 // val regWrIdxIn = Input(UInt(log2Ceil(regNums).W))
 // val regWrIdxOut = Output(UInt(log2Ceil(regNums).W))

}

class EXU (regNums:Int) extends Module {
  val io = IO(new EXUIO(regNums))
  val alu = Module(new ALU)
  
  alu.io.op                := io.duCtrl.AluOp.op

  io.aluData               <> alu.io.aluData
  //io.exuCtrl.RegFileEnable.en := io.duCtrl.RegFileEnable.en
 // io.regWrIdxOut           := io.regWrIdxIn
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

    is("b0000".U) {
      val out_temp = a5 + b5
      io.aluData.out	:= out_temp(31,0)
      io.aluFlags.cflag	:= out_temp(32)
      io.aluFlags.oflag	:= ((a5(31) && b5(31)) && ~out_temp(31)) || ((~a5(31) && ~b5(31)) && out_temp(31)) 
    }
    is("b0001".U) {
      val out_temp1 = a5 + inverse_b5
      io.aluData.out	:= out_temp1(31,0)
      io.aluFlags.cflag	:= !out_temp1(32)
      io.aluFlags.oflag	:= ((~a5(31) && b5(31)) && out_temp1(31)) || ((a5(31) && ~b5(31)) && ~out_temp1(31)) 
    }
    is("b0010".U) {
      io.aluData.out	:= ~io.aluData.a
    }
    is("b0011".U) {
      io.aluData.out	:= io.aluData.a & io.aluData.b
    }
    is("b0100".U) {
      io.aluData.out	:= io.aluData.a | io.aluData.b
    }
    is("b0101".U) {
      io.aluData.out	:= io.aluData.a ^ io.aluData.b
    }
    is("b0110".U) {
      io.aluData.out	:= io.aluData.a.asSInt < io.aluData.b.asSInt
    }
    is("b0111".U) {
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

