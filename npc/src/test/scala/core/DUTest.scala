import chisel3._
import chisel3._
import core._
import chisel3.experimental.BundleLiterals._
import chisel3.simulator.scalatest.ChiselSim
import org.scalatest.freespec.AnyFreeSpec
import org.scalatest.matchers.must.Matchers



class DUTest extends AnyFreeSpec with Matchers  with ChiselSim {

  "assign inputs and check ALU output" in {
    simulate (new DU(enableTestInit = true)) { dut =>

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
 
    //  addi x1, x1, 1 
    dut.io.inst.poke("h00108093".U)
    dut.io.regWrBackVal.poke(100.U)
    dut.clock.step()

    dut.io.aluSrc1.expect(1.U)
    dut.io.aluSrc2.expect(1.U)

    dut.io.testRdIdx.get.poke(1.U)
    dut.io.testRdVal.get.expect(100.U)
    dut.io.ctrl.AluOp.op.expect(0.U)

  }
}
}
