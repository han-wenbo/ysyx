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


NPC_BUILD_DIR = $(NPC_HOME)/build/obj_dir
NPC_OBJS      = $(notdir $(shell find $(NPC_BUILD_DIR)/ -name "*.o))

 ## the reason for getting scala files list is to get sv files list
SCALA_FILELIST_MK = $(shell find -L ./src -name "filelist.mk")
include $(SCALA_FILELIST_MK)
SCALA_SRCS-y += $(shell find $(SCALA_DIRS-y) -maxdepth 1 -name "*.scala")
SCALA_SRCS  =  $(filter-out $(SCALA_SRCS_BLACKLIST-y),$(SCALA_SRCS-y))

## scala -> sv
SCALA_SV_DIR = ./vsrc
TOP_SV = $(SCALA_SV_DIR)/Core.sv

$(TOP_SV):$(SCALA_SRCS)
	sbt "runMain core.GenCore"

######################################################
DPI_SV_DIR = ./src/main/resources
DPI_SV = $(wildcard $(DPI_SV_DIR)/*.sv)

V_BUILD_DIR = ./build/obj_dir
VTOP_CPP = $(V_BUILD_DIR)/VCore.cpp

SIM_CPP_DIR = ./csrc
SIM_CPP = $(realpath $(wildcard $(SIM_CPP_DIR)/*.cpp))  
SIM_CPP_HEADERFILE = $(realpath $(wildcard $(SIM_CPP_DIR)/*.h))   


VERILATOR  = verilator
VFLAGS += --cc $(TOP_SV) $(DPI_SV) -I$(SCALA_SV_DIR)
VFLAGS += --Mdir $(V_BUILD_DIR) 
VFLAGS += $(SIM_CPP)
VFLAGS += -CFLAGS "-g -O0 -fPIC " --lib-create npc

$(VTOP_CPP): $(TOP_SV) $(DPI_SV)
	mkdir -p $(V_BUILD_DIR)
	$(VERILATOR) $(VFLAGS)

./build/obj_dir/libnpc.so: $(VTOP_CPP) $(SIM_CPP) $(SIM_CPP_HEADERFILE)
	make -C build/obj_dir -f VCore.mk

sim:./build/obj_dir/libnpc.so

asdlasdjl:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	mkdir -p ./build/obd_dir
	##sbt "runMain core.GenCore"
	verilator  --cc Core.sv  DpiMem.sv DpiExit.sv -Ivsrc \
                ./csrc/sim_exit.cpp ./csrc/sim_main.cpp ./csrc/sim_rfile.cpp ./csrc/sim_mem.cpp\
                  --Mdir ./build/obj_dir  \
	  -CFLAGS "-g -O0 -fPIC " --lib-create libnpc
so:
	g++ -shared -o ./build/obj_dir/npc.so ./build/obj_dir/*.o
	  ## -DVL_DEBUG 
	  ##-CFLAGS "-g -O0  -fno-inline -fno-inline-functions" --build
clean:
	rm -rf ./build/obj_dir  ./build/target ./vsrc/* ./build/bin/*
include ../Makefile
.PHONY: clean all sim
