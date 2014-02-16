#http://ww1.microchip.com/downloads/mplab/X_Beta/installer.html
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
# http://ww1.microchip.com/downloads/en/DeviceDoc/xc32-v1.00-linux.zip
# http://ww1.microchip.com/downloads/en/DeviceDoc/xc32-v1.00-osx.dmg
# http://ww1.microchip.com/downloads/en/DeviceDoc/xc32-v1.00-windows.exe
PICTOOLCHAIN    = /opt/microchip/xc32/v1.00/bin/


#PICTOOLCHAIN    = /opt/microchip/xc32/v1.31/bin/
else

endif

GCCP			=$(PICTOOLCHAIN)xc32-gcc -mips16 -O1 -s 
ARP				=$(PICTOOLCHAIN)xc32-ar
BIN2HEX			=$(PICTOOLCHAIN)xc32-bin2hex
#PICTOOLCHAIN    = /usr/local/bin/
#GCCP			=$(PICTOOLCHAIN)pic32mx-gcc  -O3 -mips16 -s
#ARP				=$(PICTOOLCHAIN)pic32mx-ar
#BIN2HEX			=$(PICTOOLCHAIN)pic32mx-bin2hex
