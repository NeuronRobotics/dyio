#@ Author Kevin Harrington
SHELL := /bin/bash -e

CFILES := $(wildcard *.c) $(wildcard usb/*.c) 
OFILES := $(CFILES:%.c=%.o)

all:clean $(OFILES)

	echo ok
%.o: %.c

	$(CC_Bowler_Arch) -I../../../Platform/include/ -I../../../BowlerStack/include/ -c $< -o $@
clean:
	 rm -rf *.o
	 rm -rf *.d
	 rm -rf usb/*.o
	 rm -rf usb/*.d