# Generated Makefile
#@ Author Kevin Harrington
SHELL := /bin/bash -e

-include ../toolchain/pic32/toolchain.mk
-include ../toolchain/avr/toolchain.mk

CCP_pic32MX440F128H    		= $(GCCP) -mprocessor=32MX440F128H  
CCP_pic32MX460F512L   		= $(GCCP) -mprocessor=32MX460F512L 
CCP_pic32MX795F512L   		= $(GCCP) -mprocessor=32MX795F512L


CPU_SPD       	= 18432000UL
GCCA_full       = $(GCCA) -DF_CPU=$(CPU_SPD) -I/usr/lib/avr/include/  
CCA_avratmega324p  = $(GCCA_full) -mmcu=atmega324p 
CCA_avratmega644p  = $(GCCA_full) -mmcu=atmega644p

CCNAT    		= gcc -Os -g3 -Wall -fmessage-length=0 -MMD -MP

LIBDIR  		= ../lib


AVR_CFILES :=$(wildcard src/avr/*.c) $(wildcard ../BowlerStack/src/*.c)
AVR_FILTERED:=$(filter-out ../BowlerStack/src/Namespace_bcs_pid.c, $(AVR_CFILES))
AVR_OFILES := $(AVR_FILTERED:%.c=%.o)


PIC_CFILES :=$(wildcard src/pic32/*.c) $(wildcard src/pic32/usb/*.c) $(wildcard ../BowlerStack/src/*.c)
PIC_OFILES := $(PIC_CFILES:%.c=%.o)

NATIVE_CFILES :=$(wildcard src/native/*.c) $(wildcard ../BowlerStack/src/*.c)
NATIVE_OFILES := $(NATIVE_CFILES:%.c=%.o)

all: COMPILE
	echo "Done!"
clean:
	rm -rf $(AVR_OFILES) $(PIC_OFILES) $(NATIVE_OFILES)

COMPILE: Native pic32MX440F128H AVR324p AVR644p  pic32MX460F512L pic32MX795F512L  
	echo OK
	
Native:
	make -C src/native/  CC_Bowler_Arch="$(CCNAT)" 
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCNAT) -DNO_PRINTING -I../Platform/include/" 
	$(AR) rcs  $(LIBDIR)/native/linux/libNRLIB.a $(NATIVE_OFILES)
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCNAT) -I../Platform/include/" 
	$(AR) rcs  $(LIBDIR)/native/linux/libNRLIB_debug.a $(NATIVE_OFILES)
	make -C ../BowlerStack/ clean
	make -C src/native/  clean

AVR644p:
	echo $(AVR_OFILES)
	rm -f $(LIBDIR)/AVR/atmega644p/libNRLIB.a
	rm -f  $(LIBDIR)/AVR/atmega644p/libNRLIB_debug.a
	make -C src/avr/  CC_Bowler_Arch="$(CCA_avratmega644p)" 
	
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCA_avratmega644p) -DNO_PRINTING -I../Platform/include/" 
	$(ARAVR) rcs  $(LIBDIR)/AVR/atmega644p/libNRLIB.a $(AVR_OFILES)
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCA_avratmega644p) -I../Platform/include/" 
	$(ARAVR) rcs  $(LIBDIR)/AVR/atmega644p/libNRLIB_debug.a $(AVR_OFILES)
	rm -rf o
	mkdir o
	cd o/;ar x ../$(LIBDIR)/AVR/atmega644p/libNRLIB_debug.a
	ls -al o/*
	make -C ../BowlerStack/ clean
	make -C src/avr/ clean
	
	
AVR324p:
	make -C src/avr/  CC_Bowler_Arch="$(CCA_avratmega324p)" 
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCA_avratmega324p) -DNO_PRINTING -I../Platform/include/" 
	$(ARAVR) rcs  $(LIBDIR)/AVR/atmega324p/libNRLIB.a $(AVR_OFILES)
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCA_avratmega324p) -I../Platform/include/" 
	$(ARAVR) rcs  $(LIBDIR)/AVR/atmega324p/libNRLIB_debug.a $(AVR_OFILES)
	make -C ../BowlerStack/ clean
	make -C src/avr/ clean
	
pic32MX440F128H:
	make -C src/pic32/  CC_Bowler_Arch="$(CCP_pic32MX440F128H)" 
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCP_pic32MX440F128H) -DNO_PRINTING -I../Platform/include/" 
	$(ARP) rcs  $(LIBDIR)/PIC32/32MX440F128H/libNRLIB.a $(PIC_OFILES)
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCP_pic32MX440F128H) -I../Platform/include/" 
	$(ARP) rcs  $(LIBDIR)/PIC32/32MX440F128H/libNRLIB_debug.a $(PIC_OFILES)
	make -C ../BowlerStack/ clean
	make -C src/pic32/      clean

pic32MX460F512L:
	make -C src/pic32/  CC_Bowler_Arch="$(CCP_pic32MX460F512L)" 
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCP_pic32MX460F512L) -DNO_PRINTING -I../Platform/include/" 
	$(ARP) rcs  $(LIBDIR)/PIC32/32MX460F512L/libNRLIB.a $(PIC_OFILES)
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCP_pic32MX460F512L) -I../Platform/include/" 
	$(ARP) rcs  $(LIBDIR)/PIC32/32MX460F512L/libNRLIB_debug.a $(PIC_OFILES)
	make -C ../BowlerStack/ clean
	make -C src/pic32/      clean
	
pic32MX795F512L:
	make -C src/pic32/  CC_Bowler_Arch="$(CCP_pic32MX795F512L)" 
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCP_pic32MX795F512L) -DNO_PRINTING -I../Platform/include/" 
	$(ARP) rcs  $(LIBDIR)/PIC32/32MX795F512L/libNRLIB.a $(PIC_OFILES)
	make -C ../BowlerStack/ CC_Bowler_Arch="$(CCP_pic32MX795F512L) -I../Platform/include/" 
	$(ARP) rcs  $(LIBDIR)/PIC32/32MX795F512L/libNRLIB_debug.a $(PIC_OFILES)
	make -C ../BowlerStack/ clean
	make -C src/pic32/      clean
	
	
	

	



