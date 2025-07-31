include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/npc.mk
COMMON_CFLAGS += -march=rv32e_zicsr -mabi=ilp32e  # overwrite
LDFLAGS       += -melf32lriscv                    # overwrite

AM_SRCS += riscv/npc/libgcc/div.S \
           riscv/npc/libgcc/muldi3.S \
           riscv/npc/libgcc/multi3.c \
           riscv/npc/libgcc/ashldi3.c \
           riscv/npc/libgcc/unused.c\
           riscv/npc/start.S \
           riscv/npc/cte.c \
           riscv/npc/trap.S \
           riscv/npc/ioe.c \
           riscv/npc/timer.c \
           riscv/npc/trm.c \
           riscv/npc/mpe.c \
	   riscv/npc/input.c \
           riscv/npc/vme.c

