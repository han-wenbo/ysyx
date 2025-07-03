import chisel3._
import chisel3._
import core._
import chisel3.experimental.BundleLiterals._
import chisel3.simulator.scalatest.ChiselSim
import org.scalatest.freespec.AnyFreeSpec
import org.scalatest.matchers.must.Matchers



class FUTest extends AnyFreeSpec with Matchers  with ChiselSim {

  "assign inputs and check ALU output" in {
    simulate (new FU(enableTestInit = true)) { dut =>
       dut.reset.poke(true.B)
       dut.io.setPcEn.get.poke(false.B)
       dut.io.testSetPcVal.get.poke(0.U)
       dut.clock.step()
       dut.io.pc.expect("h8000_0000".U) 
        
       dut.reset.poke(false.B)
       dut.io.setPcEn.get.poke(true.B)
       dut.io.testSetPcVal.get.poke(0.U)
       dut.clock.step()
       dut.io.pc.expect(0.U) 

       dut.io.setPcEn.get.poke(false.B)
       dut.io.testSetPcVal.get.poke(0.U)
       dut.clock.step()
       dut.io.pc.expect(4.U) 

       dut.clock.step(10)
       dut.io.pc.expect(44.U) 

  }
}
}
