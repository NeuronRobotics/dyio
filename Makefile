-include common/Version.mk
REVISION=$(MAJOR_VER).$(MINOR_VER).$(FIRMWARE_VER)
PUB=java -jar FirmwarePublish/Publish.jar -revision=$(REVISION)
WORKSPACE=../
NRCLIB_LOCATION=$(WORKSPACE)/c-bowler/
PIC_COMPILER=xc32-v1.00-linux


all: pubDebug
	echo DyIO Firmware built OK!
upload:svnupdate update all commit
	if (test -d $(NRCLIB_LOCATION)/);then cd $(NRCLIB_LOCATION)/;make commit;	fi
	echo upload ok
dyioUpdate:update
	#used for cloning from the DyIO sources for a fork
	if (test -d ../DyIO/); then 	rsync -avz --exclude=.svn* --exclude=.project --exclude=.cproject --exclude=Makefile ../DyIO/* 				./; fi	
update:
	echo Updating...
	rm -rf $(NRCLIB_LOCATION)/lib/AVR/*
	rm -rf $(NRCLIB_LOCATION)/lib/PIC32/32MX440F128H/*
	if (!(test -d $(NRCLIB_LOCATION)/));				then cd $(WORKSPACE);git clone https://github.com/NeuronRobotics/c-bowler.git;					fi
	if (test -d $(NRCLIB_LOCATION)/);					then cd $(NRCLIB_LOCATION)/;git pull;					fi
	if (test -d $(NRCLIB_LOCATION)/);					then cd $(NRCLIB_LOCATION)/Platform;make pic32MX440F128H;		fi
	if (test -d $(NRCLIB_LOCATION)/);					then cd $(NRCLIB_LOCATION)/Platform;make AVR644p;				fi
	if (test -d $(NRCLIB_LOCATION)/);					then cd $(NRCLIB_LOCATION)/Platform;make AVR324p;				fi
	if (test -d $(NRCLIB_LOCATION)/Platform/include/); 	then rsync -avz --exclude=.svn*						$(NRCLIB_LOCATION)/Platform/include/* 					NR-Clib/include;			fi
	if (test -d $(NRCLIB_LOCATION)/BowlerStack/); 		then rsync -avz --exclude=.svn*						$(NRCLIB_LOCATION)/BowlerStack/include/* 				NR-Clib/include;			fi
	
	if (test -d $(NRCLIB_LOCATION)/lib/AVR); 			then rsync -avz --exclude=.svn* --exclude=*.r*   	$(NRCLIB_LOCATION)/lib/AVR/* 							NR-Clib/lib/AVR/;				fi
	if (test -d $(NRCLIB_LOCATION)/lib/PIC32);			then rsync -avz --exclude=.svn* --exclude=*.r*   	$(NRCLIB_LOCATION)/lib/PIC32/32MX440F128H/*				NR-Clib/lib/PIC32/32MX440F128H/;				fi
	if (test -d $(NRCLIB_LOCATION)/toolchain/); 		then rsync -avz --exclude=.svn*  					$(NRCLIB_LOCATION)/toolchain/* 							NR-Clib/toolchain;		fi
	if (test -d $(NRCLIB_LOCATION)/toolchain/); 		then rsync -avz --exclude=.svn*  					$(NRCLIB_LOCATION)/toolchain/pic32/bootloader-app/*.ld	pic/;		fi
	
	echo Done Updating...
	
svnupdate:
	svn update
commit:
	svn commit -m="Building the DyIO"
	cd ../NRSDK/fw; svn commit -m="Building the DyIO"

main:
	make -C pic all
	make -C avr all
	
bootloader:
	#http://electropepper.org/blog/item/linux-terminal-only-pic-programming
	/opt/microchip/mplabx/mplab_ide/bin/mdb.sh ./prog.txt	
	
	
pubDebug:pub
	mkdir -p FirmwarePublish/Dev/
	rm -rf FirmwarePublish/Dev/*.xml;
	#$(PUB) -core=0,pic32mx440f128h,4,pic/output/debug/output.hex 	 -output=FirmwarePublish/Dev/dyio-PICDEBUG-$(REVISION)_NO_AVR.xml
	#Debug
	#$(PUB) -core=0,pic32mx440f128h,4,pic/output/release/output.hex 	-core=1,avr_atmegaXX4p,2,avr/output/atmega644p/output.hex -output=FirmwarePublish/Dev/dyio-DEV-$(REVISION)
	#$(PUB) -core=0,pic32mx440f128h,4,pic/output/release/output.hex 	-core=1,avr_atmegaXX4p,2,avr/output/atmega644p_debug/output.hex -output=FirmwarePublish/Dev/dyio-DEV-AVRDEBUG-$(REVISION)
	$(PUB) -core=0,pic32mx440f128h,4,pic/output/debug/output.hex 	-core=1,avr_atmegaXX4p,2,avr/output/atmega644p_debug/output.hex -output=FirmwarePublish/Dev/dyio-DEV-AVRDEBUG-PICDEBUG-$(REVISION)
	#$(PUB) -core=0,pic32mx440f128h,4,pic/output/debug/output.hex 	-core=1,avr_atmegaXX4p,2,avr/output/atmega644p/output.hex -output=FirmwarePublish/Dev/dyio-DEV-PICDEBUG-$(REVISION)
	
pub:main
	mkdir -p FirmwarePublish/Release/
	rm -rf FirmwarePublish/Release/*.xml; 
	rm -rf FirmwarePublish/Release/legacy/*.xml

	$(PUB) -core=0,pic32mx440f128h,4,pic/output/release/output.hex 		-core=1,avr_atmegaXX4p,2,avr/output/atmega644p/output.hex -output=FirmwarePublish/Release/dyio-$(REVISION).xml
	#$(PUB) -core=0,pic32mx440f128h,4,pic/output/bluetooth/output.hex 	-core=1,avr_atmegaXX4p,2,avr/output/atmega644p/output.hex -output=FirmwarePublish/Release/dyio-bluetooth-$(REVISION).xml
	#$(PUB) -core=0,pic32mx440f128h,4,pic/output/release/output.hex 		-core=1,avr_atmegaXX4p,2,avr/output/atmega324p/output.hex -output=FirmwarePublish/Release/legacy/dyio-$(REVISION)_legacy.xml

	#nr-console
clean:
	make -C pic clean
	make -C avr clean
	sudo rm $(PIC_COMPILER)*
	
	
setup:
	sudo rm -rf $(PIC_COMPILER)*
	#64 bit
	#sudo apt-get install -y --force-yes avr-libc gcc-avr lib32z1 lib32ncurses5 lib32bz2-1.0 git build-essential
	#32 bit
	sudo apt-get install -y --force-yes avr-libc gcc-avr git build-essential
	wget http://ww1.microchip.com/downloads/en/DeviceDoc/$(PIC_COMPILER).zip
	unzip $(PIC_COMPILER).zip
	#wget https://nr-sdk.googlecode.com/svn/trunk/firmware/tools/$(PIC_COMPILER)-installer.run
	sudo chmod +x $(PIC_COMPILER)-installer.run
	sudo ./$(PIC_COMPILER)-installer.run
	
