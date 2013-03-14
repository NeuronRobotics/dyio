#@ Author Kevin Harrington
SHELL := /bin/bash -e

INCLUDES	    = -I../NR-Clib/include/ -I./include/ -I ../common/include -I ../NR-Clib/include/arch/pic32

-include ../NR-Clib/toolchain/pic32/toolchain.mk
-include ../common/Version.mk
DEVICEP 		= 32MX440F128H
DEFINES			= -DUSE_VELOCITY $(DYIO_VER)
CCP     		= $(GCCP) -mprocessor=$(DEVICEP) $(INCLUDES)  -I$(PICTOOLCHAIN)../pic32mx/include $(DEFINES)
LINK 			= $(GCCP) -mprocessor=$(DEVICEP) -L ../NR-Clib/lib/PIC32/$(DEVICEP)/ 
LFLAFS          = -Wl,--script="elf32pic32mx.ld",--defsym=__MPLAB_BUILD=1,--gc-sections,--report-mem

CFILES := $(wildcard ../common/src/*/*.c) \
$(wildcard src/*.c) \
$(wildcard src/*/*.c) \
$(wildcard src/*/*/*.c)

OFILES := $(CFILES:%.c=%.o)

    
all:clean release debug bluetooth
	echo PIC Build OK!

release:buildSpecificClean $(OFILES)
	$(LINK) $(OFILES) -lNRLIB  		-o output/release/output.elf $(LFLAFS)
	cd output/release/;$(BIN2HEX) 	-v -a  output.elf	
	
debug:buildSpecificClean $(OFILES)
	$(LINK) $(OFILES) -lNRLIB_debug  -o output/debug/output.elf $(LFLAFS)
	cd output/debug/;$(BIN2HEX) 	 -v -a  output.elf
	
bluetooth:buildSpecificClean	$(OFILES)
	$(CCP) -c src/Drivers/BluetoothManager.c -DHAS_BLUTOOTH	-o src/Drivers/BluetoothManager.o
	$(LINK) $(OFILES) -lNRLIB  		 -o output/bluetooth/output.elf $(LFLAFS)  
	cd output/bluetooth/;$(BIN2HEX)  -v -a  output.elf
	
buildSpecificClean:
	rm -rf src/Drivers/BluetoothManager.o

%.o: %.c
	$(CCP) -c $< -o $@
clean:
	 rm -rf $(OFILES)
lib:$(OFILES)
	$(AR) rcs  libNRLIB.a $(OFILES)