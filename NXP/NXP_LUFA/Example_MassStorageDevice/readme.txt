===============================
==                           ==
== MassStorageDevice example ==
==                           ==
===============================
This example implements a mass storage class device that operates on a FAT12
volume stored in internal RAM. The size of this volume is set by the constant
DATA_RAM_PHYSICAL_SIZE defined in DataRam.h



=====================
==                 ==
== Getting Started ==
==                 ==
=====================

This example can be built and debugged using two compiler tool chains.
Visit http://www.lpcware.com/content/project/LPCUSBlib/build-it to learn
how to setup and configure these tool chains to build this example.


===================================
==                               ==
== Compiler build configurations ==
==                               ==
===================================

The software that makes up this example is designed to run on many different
development boards. Therefore the compiler must be configured to build an image
that is targeted to the development board you are using. This section explains
how to set these build configurations for each of the supported compilers.


LPCXpresso IDE
--------------

Configure projects:
  right click on the BSP project in the project explorer window
  click Build Configurations->Set Active->(see configuration in table below)
  repeat these steps with the CDL, LPCUSBlib, and Example_MassStorageDevice

Configure MCU:
  right click on the Example_MassStorageDevice project in the project explorer window
  click Properties->C/C++ Build->MCU settings->(see configuration in table below)

Configure the indexer:
   click Window->Preferences->C/C++->Indexer->Use active build configuration

                                     BSP                 CDL           LPCUSBlib     Example_MassStorageDevice   MCU
                           ======================= ===============  ==============  =========================  ========
LPC11U14 / LPCXpresso      LPC11Uxx_LPCXpressoRevB    LPC11Uxx      LPC11Uxx_Device          LPC11Uxx          LPC11U14
LPC11U14 / MCB1000         LPC11u14_MCB1000           LPC11Uxx      LPC11Uxx_Device          LPC11Uxx          LPC11U14
LPC1768  / MCB1700         LPC1768_MCB1700            LPC17xx       LPC17xx_Device           LPC17xx           LPC1768
LPC1768  / LPCXpresso      LPC17xx_LPCXpressoRevB     LPC17xx       LPC17xx_Device           LPC17xx           LPC1768
LPC1778  / EmbeddedArtists LPC177x_8x_EAOEMBaseRevA   LPC177x_8     LPC177x_8x_Device        LPC177x_8x        LPC1778 (or LPC4088)
LPC1850  / Hitex           LPC1850_HITEX_A4           LPC18xx       LPC18xx_Device           LPC18xx           LPC1850
LPC4350  / Hitex           LPC4350_HITEX_A4           LPC43xx_M4    LPC43xx_Device           LPC43xx M4        LPC4350
LPC1830  / Xplorer         LPC1830_Xplorer            LPC18xx       LPC18xx_Device           LPC18xx           LPC1830
LPC4330  / Xplorer         LPC4330_Xplorer            LPC43xx_M4    LPC43xx_Device           LPC43xx M4        LPC4330
LPC4350  / Element14	   LPC1435_ELEMENT14	      LPC43xx_M4    LPC43xx_Device	     LPC43xx M4        LPC4350	
 


Keil uVision 4 IDE
------------------
Start the compiler by double clicking on applications\examples\LPCUSBlib\LPCUSBlib_workspace.uvmpw

Configure a Batch Build:
  click on Project->Batch Build...
  expand the BSP project to display a list of project targets
  select the project target by checking the appropriate checkbox
    (see target list in table below)
  repeat these steps with the CDL, LPCUSBlib_Device, and Example_MassStorageDevice

                             BSP                      CDL     LPCUSBlib_Device  MassStorageDevice 
                          ==========               =========  ================  =================
LPC11U14 / MCB1000         MCB1000                  LPC11Uxx   LPC11Uxx_Device      MCB1000
LPC1768  / MCB1700         MCB1700                  LPC17xx    LPC17xx_Device       MCB1700
LPC1778  / EmbeddedArtists EAOEMBaseRevA_LPC177x_8x LPC177x_8x LPC177x_8x_Device    EAOEMBaseRevA_LPC177x_8x
LPC1850  / Hitex           HITEX1800                LPC18xx    LPC18xx_Device       HITEX1800
LPC4350  / Hitex           HITEX4300                LPC43xx    LPC43xx_Device       HITEX4300
LPC1830  / Xplorer         Xplorer                  LPC18xx    LPC18xx_Device       XPLORER1830
LPC4330  / Xplorer         Xplorer                  LPC43xx    LPC43xx_Device       XPLORER4330
LPC4330  / Element14       Xplorer                  LPC43xx    LPC43xx_Device       XPLORER4330


IAR Embedded Workbench
----------------------
Start the compiler by double clicking on applications\examples\LPCUSBlib\LPCUSBlib.eww

Build the image using Batch Build
  click on Project->Batch Build...
  select the batch build based on this example name and the board you are 
    building on
  click on Make

Debug the image
  open the Workspace view
  select the Overview tab at the bottom of the window
  use the drop down list to select the configurations for this example and 
    the BSP, CDL, and LPCUSBlib libraries

                             BSP                    CDL     LPCUSBlib_Device  MassStorageDevice 
                          ==========             =========  ================  =================
LPC11U14 / MCB1000         LPC11u14_MCB1000       LPC11Uxx   LPC11Uxx_Device      MCB1000
LPC1768  / MCB1700         LPC1768_MCB1700        LPC17xx    LPC17xx_Device       MCB1700
LPC1778  / EmbeddedArtists LPC1788_EAOEMBaseRevA  LPC177x_8x LPC177x_8x_Device    LPC1788_EAOEMBaseRevA
LPC1850  / Hitex           LPC1850_HITEX_A4       LPC18xx    LPC18xx_Device       LPC1850_HITEX
LPC4350  / Hitex           LPC4350_HITEX_A4       LPC43xx    LPC43xx_Device       LPC4350_HITEX
LPC1830  / Xplorer         LPC1830_Xplorer        LPC18xx    LPC18xx_Device       Xplorer1830
LPC4330  / Xplorer         LPC4330_Xplorer        LPC43xx_M4 LPC43xx_Device       Xplorer4330



==========================================
==                                      ==
== Board connections and configurations ==
==                                      ==
==========================================


LPC18xx_HITEX (LPC1850/LPC4350 Hitex Evaluation Board)
---------------------------------------------------------------
schematic: ./BSP/schematics/SCM_LPC1850EVA-A4-2.pdf

Connect the JTAG to the 20 pin receptacle marked X4 JTAG
Connect the type-B end of a USB cable to the receptacle
  marked X2. Plug the type-A end of this cable into a PC



LPC4330_Xplorer (NGX Xplorer Evaluation Board with LPC4330)
-----------------------------------------------------------

Jumper block J4: 1=off 2=on 3=on 4=on
Connect the JTAG to the 10 pin receptacle marked J2
Connect the micro-b end of a USB cable to the receptacle
  marked USB0. Plug the type-A end of this cable into a PC



LPC1435_ELEMENT14 (Element 14 gaming board with LPC4350)
--------------------------------------------------------

Connect the JTAG to the 10 pin receptacle marked J6
Connect one end of a type-A to type-A USB cable to the
  receptacle marked USB0. Plug the other end of this cable
  into a PC



LPC11u14_MCB1000 (Keil MCB1000 development board)
-------------------------------------------------
schematic: ./BSP/schematics/mcb1000-schematics.pdf

Jumpers:
  J4 = 2-3	  (UCON - PIO0_6 pulls D+ high)
  J2 = 1-2          (VDD  - core power)
  J5 not installed  (ISP  - ISP via COMM)
  J6 not installed  (RST  - ISP via COMM)
Connect the JTAG debugger to the 10 pin Cortex Debug connector labeled J3
Connect the type-B end of a USB cable to the type-B recepticle and the type-A
  end of the cable to the USB receptacle on a PC
Once the USB cable is connected to the board the following LEDs should be
  illuminated:
    Power
    All 8 LEDs in PIO2


LPC1768_MCB1700 (Keil MCB1700 development board)
------------------------------------------------
schematic: ./BSP/schematics/mcb1700-schematics.pdf

Jumpers:
  E/U    = 1-2  (Ethernet/USB)
  UMODE  = 1-2  (USB Device Mode)
  D-     = Device
  D+     = Device
  VBUS   = 1-2
  VDDIO  = 1-2
  VDDREG = 1-2
  
Connect the JTAG debugger to the 20 pin JTAG or 10 pin Cortex Debug connector.
Connect the type-B end of a USB cable to the type-B recepticle labeled 'Device'
and the type-A end of the cable to the USB receptacle on a PC. Once the USB
cable is connected to the board the following LEDs should be illuminated:
    Power
    100MHz
    USC (LED indicates a USB soft connect from P2.9)
	

LPC177x_8x_EAOEMBaseRevA (LPC177x_8x on the Embedded Artist OEM RevA basse board)
------------------------------------------------
schematic: visit http://www.embeddedartists.com

Jumpers:
  JP15 = installed (Device detect)
  JP16 = not installed (OTG host mode)
  
Connect the JTAG debugger to the 20 pin JTAG or 10 pin Cortex Debug connector.
Connect the mini type-B end of a USB cable to the mini USB recepticle labeled 'J19'
  and the type-A end of the cable to the USB receptacle on a PC. Once the USB


NOTES: Connect the mini USB cable to J19 after the program has started to run
       USB1 is used in this example which cannot power this board.
       To power the board, use J32 (USB2 mini) or J24 (external power)

	
LPC11Uxx_LPCXpressoRevB (LPCXpresso LPC11Uxx on the LPCXpresso Rev B base board)
--------------------------------------------------------------------------------
schematic: ./BSP/schematics/lpcxpresso.lpc11u14.schematic.pdf

Running this example on the LPCXpresso LPC11U14 can be done one of two ways:

1. LPCXpresso LPC11U14 stand-alone
  	Connect the type-B end of a USB cable to the mini receptacle on the
    	LPCXpresso board labeled J8 and the type-A end to the USB receptacle on a PC

2. LPCXpresso LPC11U14 plugged into the LPCXpresso base board Rev B
  	Plug the LPCXpresso LPC11U14 board into the connector labeled J4 on a
    	LPCXpresso base board Rev B 
  	Configure the base board according to the user's guide from Embedded Artists
  	Connect the mini type-B end of a USB cable to the receptacle on the base board
    	labeled X1 and the type-A end to the USB receptacle on a PC
  	Once the USB cable is connected to the board the following LEDs should be
    	illuminated:
      	LED25  (vbus)
     	LED26  (3.3v rail)
		
For both configurations the JTAG debugger is connected to the mini USB receptacle labeled J3 on the LPCXpresso LPC11U14 board


LPC17xx_LPCXpressoRevB (LPCXpresso LPC17xx on the LPCXpresso Rev B base board)
------------------------------------------------------------------------------
schematic: ./BSP/schematics/LPCXpressoLPC1769revB.pdf

Running this example on the LPCXpresso LPC1769 can be done one of two ways:

1. LPCXpresso LPC1769 stand-alone. Solder a type-B USB receptacle onto the board
   and wire it up. See included schematics for details. Connect the type-B end
   of a USB cable to the receptacle on the LPCXpresso board and the type-A end
   to the USB receptacle on a PC

2. LPCXpresso LPC1769 plugged into the LPCXpresso base board Rev B. Plug the 
   LPCXpresso LPC1769 board into the connector labeled J4 on a LPCXpresso base
   board Rev B. Configure the base board according to the users guide from 
   Embedded Artists. Connect the mini type-B end of a USB cable to the
   receptacle on the base board labeled X1 and the type-A end to the USB
   receptacle on a PC.
   
   Once the USB cable is connected to the board the following LEDs should be
   illuminated:
      LED25  (vbus)
      LED26  (3.3v rail)
		
   For both configurations the JTAG debugger is connected to the mini USB
   receptacle labeled J3 on the LPCXpresso LPC1769 board.



======================
==                  ==
== PC configuration ==
==                  ==
======================


Use a PC running Windows XP, Vista or 7
Connect the type-A end of the USB cable that is connected to the board into one
  of the USB receptacles on the PC
Open a Windows File Explorer window



=================================
==                             ==
== Build and debug the example ==
==                             ==
=================================


LPCXpresso IDE
--------------

In the project explorer window of the IDE right click on the
  Example_MassStorageDevice project and select Debug As->C/C++ MCU Application
In the main window of the IDE click Run->Resume to start running the application



Keil uVision 4 IDE
------------------

In the Batch Build window, select the project targets as described in Compiler
  Build Configurations and then click Build
In the main window of the IDE click Debug->Start/Stop Debug Session
click Debug->Run



================================================
==                                            ==
== How this example runs and what to look for ==
==                                            ==
================================================

When the example is run and the board is connected to a PC with a USB cable it
  will enumerate on the PC as a mass storage device and show up in your Windows
  file explorer as a drive with the volume label "LPCUSBlib".

The drive will contain a single file called "README.TXT" which contains the text
  "This is a USB Memory Device demonstration. "



==================
==              ==
== Design notes ==
==              ==
==================

This Mass Storage Device example defines a virtual drive size and a physical
  drive size.
These numbers are defined in the file DataRam.h and look like this:

#define DATA_RAM_START_ADDRESS			0x20080000
#define DATA_RAM_PHYSICAL_SIZE			0xc00
#define DATA_RAM_VIRTUAL_SIZE			0x4000 /* fake capacity to trick windows */

The value of DATA_RAM_VIRTUAL_SIZE is sent to the Windows operating system in
  the SCSI Read Capacity command. This value will show up as the capacity of the
  drive when formatting.

The value of DATA_RAM_PHYSICAL_SIZE is the size of the actual buffers used in
  the device to implement the mass storage device. When the file system in
  Windows attempts to read or write past this size these reads and writes will
  be ignored.

The reason the virtual size is sent to the operating system is because Windows
  has a lower limit on drive capacities, and the size of internal RAM in some
  parts is well below this limit.

