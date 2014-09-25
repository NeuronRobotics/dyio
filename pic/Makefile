#@ Author Kevin Harrington
SHELL := /bin/bash -e

INCLUDES	    = -I../NR-Clib/include/ -I./include/ -I ../common/include -I ../NR-Clib/include/arch/pic32

-include ../NR-Clib/toolchain/pic32/toolchain.mk
-include ../common/Version.mk
LINK_DIR=../NR-Clib/lib/PIC32/$(DEVICEP)/
DEVICEP 		= 32MX440F128H
DEFINES			= -DUSE_VELOCITY $(DYIO_VER)
CCP     		= $(GCCP) -mprocessor=$(DEVICEP) $(INCLUDES)  -I$(PICTOOLCHAIN)../pic32mx/include $(DEFINES)
LINK 			= $(GCCP) -mprocessor=$(DEVICEP) -L$(LINK_DIR) 
#LFLAFS          =  -Wl,--defsym=__MPLAB_BUILD=1,-Map="dist/default/production/DyIO.X.production.map"
LFLAFS          = -Wl,--script="elf32pic32mx.ld",-Map="dyio.map" 

CFILES :=	$(wildcard ../common/src/*/*.c) \
			$(wildcard src/*.c) \
			$(wildcard src/*/*.c) \
			$(wildcard src/*/*/*.c)

OFILES := 	$(CFILES:%.c=%.o)

    
all:clean release debug 
#all: clean debug size
	echo PIC Build OK!

release:buildSpecificClean $(OFILES)
	mkdir -p output/release/
	$(LINK) $(OFILES) -lNRLIB  		-o output/release/output.elf $(LFLAFS)
	cd output/release/;$(BIN2HEX) 	-v -a  output.elf	
	
debug:buildSpecificClean $(OFILES)
	mkdir -p output/debug/
	$(LINK) $(OFILES) -lNRLIB_debug  -o output/debug/output.elf $(LFLAFS)
	cd output/debug/;$(BIN2HEX) 	 -v -a  output.elf
	
bluetooth:buildSpecificClean	$(OFILES)
	mkdir -p output/bluetooth/
	$(CCP) -c src/Drivers/BluetoothManager.c -DHAS_BLUTOOTH	-o src/Drivers/BluetoothManager.o
	$(LINK) $(OFILES) -lNRLIB  		 -o output/bluetooth/output.elf $(LFLAFS)  
	cd output/bluetooth/;$(BIN2HEX)  -v -a  output.elf
	
buildSpecificClean:
	rm -rf src/Drivers/BluetoothManager.o

%.o: %.c
	$(CCP) -c $< -o $@
clean:
	 rm -rf $(OFILES)
	 mkdir -p output/o/
	 rm  -rf output/o/*
size:
	mkdir -p output/o/
	rm  -rf output/o/*
	cp $(OFILES) output/o/
	cp $(LINK_DIR)libNRLIB_debug.a output/o/
	cd output/o/;xc32-ar x libNRLIB_debug.a
	sh size.sh
	xc32-size output/debug/output.elf


