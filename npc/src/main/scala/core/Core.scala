
package core
import chisel3.util._
import _root_.circt.stage.ChiselStage
import chisel3._
import chisel3.dontTouch

import java.nio.file.{Files, Paths}
import java.nio.charset.StandardCharsets
class Core (enableTestInit:Boolean) extends Module {
  val io = IO(new Bundle{ 
      val instAddr = Output(UInt(32.W))
//    val instIn   = Input(UInt(32.W))

    // test for write value into registers.
    val testEn    : Option[Bool]  = if(enableTestInit)  Some(Input(Bool())) else None 
    val testIdx   : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testVal   : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(32.W))) else None

    // test for read value from Register file
    val testRdIdx : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    val testRdVal : Option[UInt]  = if(enableTestInit)  Some(Output(UInt(32.W))) else None


    // test for set pc
     val setPcEn   : Option[Bool] = if (enableTestInit) Some(Input(Bool())) else None
     val testSetPcVal : Option[UInt] = if (enableTestInit) Some(Input(UInt(32.W))) else None

  })

 val FU  = Module(new FU(enableTestInit))  
 val DU  = Module(new DU(enableTestInit))
 val EXU = Module(new EXU(16))
 val MU  = Module(new MU)
 val WBU = Module(new WBU(16))

 
 // Connection between FU, Top, and I-Cache
   io.instAddr := FU.io.toDU.pc
 //FU.io.instIn  := io.instIn 

 // FU -> DU
 FU.io.toDU <> DU.io.fromFU

 // DU -> EXU
 EXU.io.fromDU     <> DU.io.toEXU
 EXU.io.duCtrl    <> DU.io.ctrl
 //EXU.io.regWrIdxIn := DU.io.regWrIdx

 
 // EXU -> MU
 MU.io.fromEXU   <> EXU.io.toMU
 MU.io.exuCtrl   <> EXU.io.exuCtrl

 // MU -> WBU
 WBU.io.muCtrl <> MU.io.muCtrl 
 WBU.io.memWbVal := MU.io.memWbVal
 WBU.io.aluWbVal := MU.io.aluWbVal
 WBU.io.snpcWbVal := MU.io.snpcWbVal

 // MU -> FU
 FU.io.aluPc     := MU.io.aluPc
 FU.io.pcSrcSel  := MU.io.pcSrcSel

 // WBU -> DU
 // When pipelizing, need this code
 DU.io.regWrBackVal := WBU.io.wbValOut 
 //DU.io.regWrIdx     := WBU.io.regWrIdxOut
// DU.io.regWrbackEn.en  := WBU.io.needWB.RegFileWbEnable.en 



dontTouch(DU.io)
dontTouch(EXU.io)
dontTouch(MU.io)
dontTouch(WBU.io)

 // Register file test interfaces.
 if(enableTestInit) {
   DU.io.testEn.get := io.testEn.get
   DU.io.testIdx.get:= io.testIdx.get
   DU.io.testVal.get:= io.testVal.get

   DU.io.testRdIdx.get  := io.testRdIdx.get
   io.testRdVal.get := DU.io.testRdVal.get

   FU.io.setPcEn.get := io.setPcEn.get
   FU.io.testSetPcVal.get := io.testSetPcVal.get
 }
}


/*object GenCore extends App {
  ChiselStage.emitSystemVerilogFile(
    new Core(true),
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info", "-default-layer-specialization=enable")
  )
}*/ 

object GenCore extends App {
  // 自动创建输出目录
  val outPath = Paths.get("vsrc")
  if (!Files.exists(outPath)) Files.createDirectories(outPath)

  // 生成 SystemVerilog（使用 firtool 后端）
  ChiselStage.emitSystemVerilog(
    new Core(true),
    firtoolOpts = Array(
      "-split-verilog",                    // 拆分多个模块
      "-o", "vsrc",                        // 注意：必须分开写，firtool 1.114.1 不支持 "-o=..."
      "-disable-all-randomization",
      "-strip-debug-info"
    )
  )
}
