TSRC ?= aaaaasadip.S
TOUT = $(basename $(TSRC))

TSRC_DIR = tsrc
TOUT_DIR = build/bin
TSRC_PATH = $(TSRC_DIR)/$(TSRC)
TOUT_PATH  = $(TOUT_DIR)/$(TOUT)

TOBJ = $(TOUT_DIR)/$(TOUT).o
TBIN = $(TOUT_DIR)/$(TOUT).bin


$(TOBJ) : $(TSRC_PATH)
	mkdir -p ./build/bin 
	riscv64-unknown-elf-as $< -o $@
$(TBIN) : $(TOBJ)
	riscv64-unknown-elf-objcopy -O binary $< $@ 
cpbin : $(TBIN)

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	mkdir -p ./build/obd_dir
	sbt "runMain core.GenCore"
	verilator  --cc Core.sv  DpiMem.sv DpiExit.sv -Ivsrc \
          --exe       ./csrc/sim_exit.cpp ./csrc/sim_main.cpp ./csrc/sim_rfile.cpp ./csrc/sim_mem.cpp\
	    --trace  --debug  \
                  --Mdir ./build/obj_dir  \
	  -CFLAGS "-g -O0 -fPIC " --build 
so:
	g++ -shared -o ./build/obj_dir/npc.so ./build/obj_dir/*.o
	  ## -DVL_DEBUG 
	  ##-CFLAGS "-g -O0  -fno-inline -fno-inline-functions" --build
clean:
	rm -rf ./build/obj_dir  ./build/target ./vsrc/* ./build/bin/*
include ../Makefile
.PHONY: clean all sim
