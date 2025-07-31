package core
import chisel3._
import chisel3.util._

object OpCode {
  val TYPE_I  = "b0010011".U
  val TYPE_IL = "b0000011".U
  val TYPE_IJ = "b1100111".U
  val TYPE_IE = "b1110011".U
  val TYPE_S  =  "b0100011".U
  val TYPE_B  =  "b1100011".U
  val TYPE_J  =  "b1101111".U
  val TYPE_UA =  "b0010111".U
  val TYPE_UL =  "b0110111".U
}

class IMMGU extends Module {
  val io = IO(new Bundle { 
    val inst   = Input(UInt(32.W))
    val imm    = Output(UInt(32.W))
  }) 
  val inst = io.inst 
  val opcode =  inst(6,0)

  val immI = Fill(20, inst(31)) ## inst(31,20)
  val immU = inst(31,12)        ## Fill(12, 0.U(1.W))
  val immS = Fill(20, inst(31)) ## inst(31,25) ## inst(11,7)
  val immJ = Fill(12, inst(31)) ## inst(31)    ## inst(19,12) ## inst(20,20) ## inst(30,21)  ## 0.U(1.W)
  val immB = Fill(19, inst(31)) ## inst(31)    ## inst(7)     ## inst(30,25) ## inst(11, 8)  ## 0.U(1.W)

  io.imm := MuxLookup(opcode, 0.U)(
    Seq(
     OpCode.TYPE_I  -> immI,
     OpCode.TYPE_IL -> immI,
     OpCode.TYPE_IJ -> immI,
     OpCode.TYPE_IE -> immI,
     OpCode.TYPE_S  -> immS,
     OpCode.TYPE_B  -> immB,
     OpCode.TYPE_J  -> immJ,
     OpCode.TYPE_UA -> immU,
     OpCode.TYPE_UL -> immU
    )
  )

}
