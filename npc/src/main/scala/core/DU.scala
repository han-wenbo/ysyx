package core
import chisel3._
import chisel3.util._
import core._
import core.control._
import chisel3.util.experimental.decode._
import chisel3.ChiselEnum
import chisel3.util.BitPat
import core.control.InstDecode._

class DU (enableTestInit : Boolean = false) extends Module {
  val io = IO(new Bundle {

    val ctrl         = Output(new DUCtrl) 
    val toFUCtrl     = Output(new DU2FUCtrl)

    val fromFU       = Flipped(new FUtoDUIO)
    val toFU         = new DUtoFUIO
    val toEXU        = new DUtoEXUIO

    val regWrBackVal = Input(UInt(32.W))
    //val regWrbackEn  = Input(new ctrlRegFileWbEnable)  
    //val regWrIdx     = Input(UInt(4.W))     


    /* for unit test */
    val testEn    : Option[Bool]  = if(enableTestInit)  Some(Input(Bool())) else None 
    val testIdx   : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testVal   : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(32.W))) else None
    
    val testRdIdx : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testRdVal : Option[UInt]  = if(enableTestInit)  Some(Output(UInt(32.W))) else None

    /************* RegFile test interfaces ************/
    val testReadRegs =
      if (enableTestInit) Some(Output(Vec(16, UInt(32.W))))
      else None
  }) 
  


  val rd   = io.fromFU.inst(11,7)
  val rs1  = io.fromFU.inst(19,15)
  val rs2  = io.fromFU.inst(24,20)
  val fun3 = io.fromFU.inst(14,12)

  val instDecoder = Module(new InstDecoder)
  val regFile     = Module(new RegFile(enableTestInit,16))
  val immGenU     = Module(new IMMGU) 
  val csr = Module(new Csr(enableTestInit)) 
  /****** Immidiate number generator uint's connection.  ******/
  immGenU.io.inst := io.fromFU.inst
  val imm = immGenU.io.imm  
  



  /************ Instruction Decoder *************/
  instDecoder.io.inst := io.fromFU.inst
 
  // io.regWrIdxOut := rd
  io.ctrl.AluOp.op := instDecoder.io.ctrl.AluOp.op 
  io.ctrl.MemRead.memRead := instDecoder.io.ctrl.MemRead.memRead 
  io.ctrl.RegWbSrcSel.regWbSrcSel := instDecoder.io.ctrl.RegWbSrcSel.regWbSrcSel
  io.ctrl.RegWbValExtSel.regWbValExtSel := instDecoder.io.ctrl.RegWbValExtSel.regWbValExtSel
  //io.ctrl.RegFileWbEnable.en := instDecoder.io.ctrl.RegFileWbEnable.en
  io.ctrl.JmpInst.jmpInst := instDecoder.io.ctrl.JmpInst.jmpInst
  io.ctrl.BranchInst.branchInst := instDecoder.io.ctrl.BranchInst.branchInst 

  io.ctrl.MemWrMask.memWrMask     := instDecoder.io.ctrl.MemWrMask.memWrMask 
  io.ctrl.MemWrEn.memWrEn         := instDecoder.io.ctrl.MemWrEn.memWrEn 
  


  /**********  General Purpose Register File **********/

  // register file inputs 
  regFile.io.rregIdx1 := rs1
  regFile.io.rregIdx2 := rs2


  //val wEnable  =  if(enableTestInit) io.testEn.getOrElse(false.B) || io.regWrbackEn.en else io.regWrbackEn.en 
  val wEnable  =  
    if(enableTestInit) 
      io.testEn.getOrElse(false.B) ||  instDecoder.io.ctrl.RegFileWbEnable.en 
    else 
      instDecoder.io.ctrl.RegFileWbEnable.en
                  
  //val wregIdx  =  if(enableTestInit) Mux( io.testEn.getOrElse(false.B), io.testIdx.getOrElse(0.U), io.regWrIdx) else io.regWrIdx 
  val wregIdx  =  
    if(enableTestInit) 
      Mux( io.testEn.getOrElse(false.B), io.testIdx.getOrElse(0.U), rd) 
    else
      rd 
                  
  val wwregVal = Mux(csr.io.wEnable.csrWbEnable, csr.io.csrVal, io.regWrBackVal)
  val wregVal  =  
    if(enableTestInit) 
      Mux(io.testEn.getOrElse(false.B), io.testVal.getOrElse(0.U), wwregVal) 
    else 
      io.regWrBackVal 


  regFile.io.wEnable.en   := wEnable 
  regFile.io.wregIdx      := wregIdx 
  regFile.io.wregVal      := wregVal 


  /************* DU's outputs *************/

  io.toEXU.aluSrc1 := MuxLookup(instDecoder.io.ctrl.AluSrc1Sel.aluSrc1Sel,0.U) (Seq(
    "b00".U -> io.fromFU.pc,
    "b01".U -> regFile.io.rregVal1,
    "b10".U -> 0.U
  ))
  io.toEXU.aluSrc2 := Mux (instDecoder.io.ctrl.AluSrc2Sel.muxSel, regFile.io.rregVal2, imm) 

  io.toEXU.cmperSrc1 := regFile.io.rregVal1
  io.toEXU.cmperSrc2 := regFile.io.rregVal2

  io.toEXU.bInstFunc3 := fun3 
  io.toEXU.snpc := io.fromFU.snpc
 
  // the second resource register's value.
  io.toEXU.rs2Val := regFile.io.rregVal2

  if(enableTestInit) regFile.io.testRdIdx.get := io.testRdIdx.get
  if(enableTestInit) io.testRdVal.get := regFile.io.testRdVal.get


  /***************  The CSR Module ***************/
  
  // For csr instrctions usage.
  csr.io.rregIdx := imm
  csr.io.wEnable.csrWbEnable := instDecoder.io.ctrl.CsrWbEnable.csrWbEnable
 
  // When it is necessary to implement CSSR_I instructions, here should be modified.
  csr.io.immRs1     := regFile.io.rregVal1
  csr.io.csrInsFunc3 := fun3


  // Used for Trap
  csr.io.trapInst := instDecoder.io.ctrl.TrapInst.trapInst
  csr.io.mcause    := 11.U
  csr.io.mepc      := io.fromFU.pc
  
  io.toFU.vec := csr.io.mtvec
  io.toFU.mepc := csr.io.mepcOut

  io.toFUCtrl.TrapInst.trapInst := instDecoder.io.ctrl.TrapInst.trapInst 
  io.toFUCtrl.ToMepc.toMepc     := instDecoder.io.ctrl.ToMepc.toMepc 


  /************* RegFile test interfaces ************/
  if (enableTestInit) {
    for (i <- 0 until 16) {
      io.testReadRegs.get(i) := regFile.io.testReadRegs.get(i)
    }
  }
}


class InstDecoder extends Module {
   val io = IO(new Bundle{ 
      val inst = Input(UInt(32.W))
      val ctrl = Output(new allCtrl)
   })
  val ebreak = Module(new SimExitBlackBox)
  val jal_jalr = Module(new SimFtraceBlackBox)
  val triSg = Wire(Bool())

  triSg := false.B
  ebreak.io.triSg := triSg
  ebreak.io.clock := clock
  when (io.inst === "b00000000000100000000000001110011".U){
     triSg := true.B
  }


  jal_jalr.io.is_jal_jalr  := false.B
  when (io.inst === BitPat("b???????_?????_?????_???_?????_11011_11")  || 
        io.inst === BitPat("b???????_?????_?????_000_?????_11001_11")) 
  {
     jal_jalr.io.is_jal_jalr := true.B
  }

  val result = decodeTbl.decode(io.inst)  
  io.ctrl.RegFileWbEnable.en      := result(RegFileWbEnableObj).asBool
  io.ctrl.AluSrc2Sel.muxSel       := result(AluSrc2SelObj).asBool
  io.ctrl.AluSrc1Sel.aluSrc1Sel   := result(AluSrc1SelObj)
  io.ctrl.AluOp.op                := result(AluOpFieldObj) 
  io.ctrl.MemRead.memRead         := result(MemReadObj).asBool
  io.ctrl.RegWbSrcSel.regWbSrcSel := result(RegWbSrcSelObj)
  io.ctrl.JmpInst.jmpInst         := result(JmpInstObj).asBool
  io.ctrl.BranchInst.branchInst := result(BranchInstObj).asBool
  io.ctrl.MemWrEn.memWrEn         := result(MemWrEnObj).asBool
  io.ctrl.MemWrMask.memWrMask         := result(MemWrMaskObj)
  io.ctrl.RegWbValExtSel.regWbValExtSel        := result(RegWbValExtSelObj)

  
  io.ctrl.CsrWbEnable.csrWbEnable        := result(CsrWbEnableObj).asBool
  io.ctrl.TrapInst.trapInst            := result(TrapInstObj).asBool
  io.ctrl.ToMepc.toMepc            := result(ToMepcObj).asBool
}

class SimFtraceBlackBox extends BlackBox with HasBlackBoxResource {
   val io = IO(new Bundle { 
      val is_jal_jalr = Input(Bool())
   })

   addResource("/DpiExit.sv")
}
class SimExitBlackBox extends BlackBox with HasBlackBoxResource {
   val io = IO(new Bundle { 
      val triSg = Input(Bool())
      val clock = Input(Clock())
   })

   addResource("/DpiExit.sv")

}
