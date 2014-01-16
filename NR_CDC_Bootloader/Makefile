
# Generated Makefile
#@ Author Kevin Harrington
# Assumes pk2cmd (PICkit 2 programmer) and ICSP connection to MCU.

-include ../NR-Clib/toolchain/pic32/toolchain.mk
-include ../DyIO/common/Version.mk

#Old programmers
UBW  = ubw32 -r -n -w
PK2    = pk2cmd -P -R -M -F

HEX    = NR_CDC_Bootloader.hex

CC     = $(GCCP) $(DYIO_VER) -I../DyIO/common/include -I../NR-Clib/include/ -I./include/ -c
LL     = $(GCCP)  -s -L../NR-Clib/lib/PIC32/$(DEVICE) 
LFLAG_DYIO 	=  -L$(PWD)/../NR-Clib/lib/PIC32/32MX440F128H/
LFLAG_UBW_O	=  -L$(PWD)/../NR-Clib/lib/PIC32/32MX460F512L
LFLAG_UBW_N	=  -L$(PWD)/../NR-Clib/lib/PIC32/32MX795F512L
CCFLAGS = ''
HEXCONVERT = $(BIN2HEX) -v -a


ELF    = NR_CDC_Bootloader_Struder.elf

all:dyio
		
dyio:
	$(CC) -mprocessor=32MX440F128H  -DDYIO  src/main.c -o "release/main.o"  $(FLAGS)
	$(CC) -mprocessor=32MX440F128H  -DDYIO  src/flash.c -o "release/flash.o"  $(FLAGS)
	$(CC) -mprocessor=32MX440F128H  -DDYIO  src/led.c -o "release/led.o"  $(FLAGS)
	$(CC) -mprocessor=32MX440F128H  -DDYIO  src/AVRInterface.c -o "release/AVRInterface.o"  $(FLAGS)
	$(LL) $(LFLAG_DYIO) -mprocessor=32MX440F128H  "release/main.o" "release/led.o" "release/flash.o" "release/AVRInterface.o"  -lNRLIB  -o DyIO_$(ELF) $(LLFLAGS)
	$(HEXCONVERT) DyIO_$(ELF)
servostruder:
	$(CC) -mprocessor=32MX440F128H  -DSERVOSTRUDER  src/main.c -o "release/main.o"  $(FLAGS)
	$(CC) -mprocessor=32MX440F128H  -DSERVOSTRUDER  src/flash.c -o "release/flash.o"  $(FLAGS)
	$(CC) -mprocessor=32MX440F128H  -DSERVOSTRUDER  src/led.c -o "release/led.o"  $(FLAGS)
	$(CC) -mprocessor=32MX440F128H  -DSERVOSTRUDER  src/AVRInterface.c -o "release/AVRInterface.o"  $(FLAGS)
	$(LL) $(LFLAG_DYIO) -mprocessor=32MX440F128H  "release/main.o" "release/led.o" "release/flash.o" "release/AVRInterface.o"  -lNRLIB  -o DyIO_$(ELF) $(LLFLAGS)
	$(HEXCONVERT) DyIO_$(ELF)
ubw_old:
	$(CC) -mprocessor=32MX460F512L -DUBW_OLD  src/main.c -o "release/main.o"  $(FLAGS)
	$(CC) -mprocessor=32MX460F512L -DUBW_OLD  src/flash.c -o "release/flash.o"  $(FLAGS)
	$(CC) -mprocessor=32MX460F512L -DUBW_OLD  src/led.c -o "release/led.o"  $(FLAGS)
	$(CC) -mprocessor=32MX460F512L -DUBW_OLD  src/AVRInterface.c -o "release/AVRInterface.o"  $(FLAGS)
	$(LL) $(LFLAG_UBW_O) -mprocessor=32MX460F512L -DUBW_OLD  "release/main.o" "release/led.o" "release/flash.o" "release/AVRInterface.o"  -lNRLIB  -o ubw_old_$(ELF) $(LLFLAGS)
	$(HEXCONVERT) ubw_old_$(ELF)
ubw:
	$(CC) -mprocessor=32MX795F512L -DUBW_NEW  src/main.c -o "release/main.o"  $(FLAGS)
	$(CC) -mprocessor=32MX795F512L -DUBW_NEW  src/flash.c -o "release/flash.o"  $(FLAGS)
	$(CC) -mprocessor=32MX795F512L -DUBW_NEW  src/led.c -o "release/led.o"  $(FLAGS)
	$(CC) -mprocessor=32MX795F512L -DUBW_NEW  src/AVRInterface.c -o "release/AVRInterface.o"  $(FLAGS)
	$(LL) $(LFLAG_UBW_N) -mprocessor=32MX795F512L -DUBW_OLD  "release/main.o" "release/led.o" "release/flash.o" "release/AVRInterface.o"  -lNRLIB  -o ubw_new_$(ELF) $(LLFLAGS)
	$(HEXCONVERT) ubw_new_$(ELF)
aimeth:
	$(CC) -mprocessor=32MX795F512L -DAIM_ETH  src/main.c -o "release/main.o"  $(FLAGS)
	$(CC) -mprocessor=32MX795F512L -DAIM_ETH src/flash.c -o "release/flash.o"  $(FLAGS)
	$(CC) -mprocessor=32MX795F512L -DAIM_ETH  src/led.c -o "release/led.o"  $(FLAGS)
	$(CC) -mprocessor=32MX795F512L -DAIM_ETH  src/AVRInterface.c -o "release/AVRInterface.o"  $(FLAGS)
	$(LL) $(LFLAG_UBW_N) -mprocessor=32MX795F512L -DAIM_ETH  "release/main.o" "release/led.o" "release/flash.o" "release/AVRInterface.o"  -lNRLIB  -o aim_eth_$(ELF) $(LLFLAGS)
	$(HEXCONVERT) aim_eth_$(ELF)

writeUBW:
	pk2cmd -P -E
	$(PK2)ubw_new_$(HEX)
	
writeUBW_OLD:
	pk2cmd -P -E
	$(PK2)ubw_old_$(HEX)
writeDyIO:
	pk2cmd -P -E
	$(PK2)DyIO_$(HEX)
