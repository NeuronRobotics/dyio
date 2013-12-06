#@ Author Kevin Harrington
SHELL := /bin/bash -e

CFILES := $(wildcard *.c)
OFILES := $(CFILES:%.c=%.o)

#ifndef CC_Bowler_Arch
#    $(error CC_Bowler_Arch is undefined)
#endif

all:clean $(OFILES)
	echo ok
%.o: %.c
	$(CC_Bowler_Arch) -I../../../Platform/include/ -I../../../BowlerStack/include/ -c $< -o $@
clean:
	 rm -rf *.o
	 rm -rf *.d