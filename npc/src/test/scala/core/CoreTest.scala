
import chisel3._
import chisel3._
import core._
import chisel3.experimental.BundleLiterals._
import chisel3.simulator.scalatest.ChiselSim
import org.scalatest.freespec.AnyFreeSpec
import org.scalatest.matchers.must.Matchers



class CoreTest extends AnyFreeSpec with Matchers  with ChiselSim {

  "assign inputs and check ALU output" in {
    simulate (new Core(enableTestInit = true)) { dut =>

      // Set all registers' value to 1.
      dut.io.testEn.get.poke(true.B)
      for( i <- 1 to 15) {
        dut.io.testIdx.get.poke(i.U)
        dut.io.testVal.get.poke(i.U)
        dut.io.testRdIdx.get.poke(i.U)
        dut.clock.step()
        dut.io.testRdVal.get.expect(i.U)

        
      }
      dut.io.testEn.get.poke(false.B)  
    dut.reset.poke(true.B) 
      dut.clock.step()
      println(f"instAddr = 0x${dut.io.instAddr.peek().litValue}%08x")
      dut.reset.poke(false.B) 
      dut.io.instAddr.expect("h8000_0000".U)
      dut.clock.step()
      dut.io.instAddr.expect("h8000_0004".U)
      
/* 
    //  addi x5, x7, 100 
    dut.io.inst.poke("b000000011001_00111000001010010011".U)
    dut.io.regWrBackVal.poke(100.U)
    dut.io.regWrbackEn.en.poke(true.B)
    dut.io.regWrIdx.poke(1.U)
    dut.clock.step()

    dut.io.aluSrc1.expect(7.U)
    dut.io.aluSrc2.expect(25.U)
    dut.io.regWrIdxOut.expect(5.U)
    dut.io.ctrl.RegFileEnable.en.expect(true.B)
    dut.io.ctrl.AluOp.op.expect(0.U)

   //  add x2, x1,x2
   dut.io.inst.poke("b0000000_00010_00001_000_00010_0110011".U)
   dut.io.aluSrc1.expect(100.U)
    dut.io.aluSrc2.expect(2.U)
    dut.io.regWrIdxOut.expect(2.U)
    dut.io.ctrl.RegFileEnable.en.expect(true.B)
    dut.io.ctrl.AluOp.op.expect(0.U)
*/

  }
}
}
