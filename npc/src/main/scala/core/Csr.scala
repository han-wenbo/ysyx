package core
import chisel3._
import core.control._
import chisel3.util.log2Ceil
import java.lang
import core.CsrConsts._
import chisel3.util._

//#define MSTATUS 0x300
//#define MEPC    0x341     
//#define MCAUSE  0x342
//#define MTVEC   0x305

object CsrConsts{
  val  MSTATUS  = 0x300.U(12.W)
  val _MSTATUS  = 0x000.U(5.W)

  val  MTVEC    = 0x305.U(12.W)
  val _MTVEC    = 0x001.U(5.W)

  val  MEPC     = 0x341.U(12.W)
  val _MEPC     = 0x002.U(5.W)

  val  MCAUSE   = 0x342.U(12.W)
  val _MCAUSE   = 0x003.U(5.W) 

  val CSRRWF3   = 0x01.U(3.W)
  val CSRRSF3   = 0x02.U(3.W)
}


class Csr (val enableTestInit : Boolean) extends Module {

  val io = IO(new Bundle{
      
      // Used for the six csr instrcutions.
      val rregIdx  = Input(UInt(log2Ceil(4096).W))

      val wEnable       = Input(new ctrlCsrWbEnable)
      val immRs1        = Input(UInt(32.W))
      val csrInsFunc3   = Input(UInt(3.W))
      val csrVal        = Output(UInt(32.W))

      // Used for the occurance of trap
      val trapInst = Input(Bool())
      val mcause         = Input(UInt(32.W))
      val mepc           = Input(UInt(32.W))
      val mtvec          = Output(UInt(32.W))

      // mretInst
      val mepcOut           = Output(UInt(32.W))
      
    /******* Used for copying values in csrs to nemu each cycle *******/ 
    //val testRdIdx : Option[UInt]  = if(enableTestInit)  Some(Input(UInt(4.W))) else None
    //val testRdVal : Option[UInt]  = if(enableTestInit)  Some(Output(UInt(32.W))) else None
   })

    val idx = MuxLookup(io.rregIdx, 0.U) (Seq(
      MSTATUS -> _MSTATUS,
      MTVEC   -> _MTVEC,
      MEPC    -> _MEPC,
      MCAUSE  -> _MCAUSE
      ))
  
    // The definations of CSR:
    val mepc    = Reg(UInt(32.W))
    val mcause  = Reg(UInt(32.W))
    val mtvec   = Reg(UInt(32.W))
    val mstatus = Reg(UInt(32.W))

    
   /*********** Updates the CSR when executing  a csr instrcution. *************/
   // Read Logic
    val rdata = Wire(UInt(32.W)) 
    rdata := 0.U
    io.csrVal := rdata
    switch(io.rregIdx) {
       is(MSTATUS) { rdata   := mstatus }
       is(MCAUSE)  { rdata   := mcause  }
       is(MEPC)    { rdata   := mepc    }
       is(MTVEC)   { rdata   := mtvec   }
    }

   // Write Logic
    val newVal = Wire(UInt(32.W))
    newVal := 0.U
    switch(io.csrInsFunc3) {
      is(CSRRWF3) { newVal := io.immRs1 }
      is(CSRRSF3) { newVal := rdata | io.immRs1  }
    }

    when(io.wEnable.csrWbEnable) {
      switch(io.rregIdx) {
        is(MSTATUS) { mstatus := newVal }
        is(MCAUSE)  { mcause  := newVal }
        is(MEPC)    { mepc    := newVal }
        is(MTVEC)   { mtvec   := newVal }
      }
    }



  /********** When a trap happens **********/
  io.mtvec := mtvec
  
  when(io.trapInst) {
    mepc   := io.mepc
    mcause := io.mcause
  }
 
  /********** Used for mret *********/
  io.mepcOut := mepc



  /******* Used for copying values in csrs to nemu each cycle *******/ 
//  if(enableTestInit) io.t 
}
