#@ Author Kevin Harrington
SHELL := /bin/bash -e

CFILES := $(wildcard src/*.c)
OFILES := $(CFILES:%.c=%.o)
DFILES := $(CFILES:%.c=%.d)
#ifndef CC_Bowler_Arch
#    $(error CC_Bowler_Arch is undefined)
#endif
    
all:clean $(OFILES)
	echo ok
%.o: %.c
	$(CC_Bowler_Arch) -Iinclude -c $< -o $@
clean:
	 rm -rf $(OFILES)
	 rm -rf $(DFILES)
	 
lib:$(OFILES)
	$(AR) rcs  libNRLIB.a $(OFILES)