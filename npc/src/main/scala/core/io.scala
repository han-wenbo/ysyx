package core

import chisel3._
import chisel3.util._

class DUtoFUIO extends Bundle {
  val vec = Output(UInt(32.W))
  val mepc = Output(UInt(32.W))
}
class FUtoDUIO extends Bundle { 
  val pc       = Output(UInt(32.W))
  val snpc     = Output(UInt(32.W))
  val inst     = Output(UInt(32.W))
}

class DUtoEXUIO extends Bundle {
  val aluSrc1      = Output(UInt(32.W))
  val aluSrc2      = Output(UInt(32.W))

  val cmperSrc1    = Output(UInt(32.W)) 
  val cmperSrc2    = Output(UInt(32.W)) 

  val bInstFunc3   = Output(UInt(3.W))
  val snpc         = Output(UInt(32.W))

  val rs2Val       = Output(UInt(32.W))
}

class EXUtoMU extends Bundle {
  val aluResult  = Output(UInt(32.W)) 
  val branchTrue = Output(Bool())
  val snpc       = Output(UInt(32.W))

  val rs2Val       = Output(UInt(32.W))
}
