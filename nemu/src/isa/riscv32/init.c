/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <memory/paddr.h>

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
/*static const uint32_t img [] = {
  0x00108093,  // auipc t0,0
  0x00108093,  // sb  zero,16(t0)
  0x0102c503,  // lbu a0,16(t0)
  0x00100073,  // ebreak (used as nemu_trap)
  0xdeadbeef,  // some data
};*/

static const uint32_t img [] = {
  0x00100093,  // ADDI x1, x0, 1
  0x00200113,  // ADDI x2, x0, 2
  0x00300193,  // ADDI x3, x0, 3
  0x00400213,  // ADDI x4, x0, 4
  0x00500293,  // ADDI x5, x0, 5
  0x00600313,  // ADDI x6, x0, 6
  0x00700393,  // ADDI x7, x0, 7
  0x00800413,  // ADDI x8, x0, 8
  0x00900493,  // ADDI x9, x0, 9
  0x00a00513,  // ADDI x10, x0, 10
  0x00b00593,  // ADDI x11, x0, 11
  0x00c00613,  // ADDI x12, x0, 12
  0x00d00693,  // ADDI x13, x0, 13
  0x00e00713,  // ADDI x14, x0, 14
  0x00f00793,  // ADDI x15, x0, 15
	       0x00100073,
};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = RESET_VECTOR;

  /* The zero register is always 0. */
  cpu.gpr[0] = 0;
}

void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
}
