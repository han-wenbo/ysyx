/*
import chisel3._
import chisel3._
import core._
import chisel3.experimental.BundleLiterals._
import chisel3.simulator.scalatest.ChiselSim
import org.scalatest.freespec.AnyFreeSpec
import org.scalatest.matchers.must.Matchers
class EXUTest extends AnyFreeSpec with Matchers  with ChiselSim {

  "assign inputs and check ALU output" in {
    simulate (new EXU(16)) { dut =>
      // 给 ALU 数据输入赋值
      dut.io.aluData.a.poke(15.U)
      dut.io.aluData.b.poke(10.U)

      // 给控制信号赋值
      dut.io.duCtrl.AluOp.op.poke(0.U) // 例如加法
      dut.io.duCtrl.RegFileWbEnable.en.poke(true.B)

      // 推进一个周期
      dut.clock.step()

      // 验证输出
      dut.io.aluData.out.expect(25.U)
      dut.io.exuCtrl.RegFileWbEnable.en.expect(true.B)
    }
  }
}
*/
