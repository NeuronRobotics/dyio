===============================
==                           ==
== GenericHIDDevice example ==
==                           ==
===============================

This example implements a generic HID device. It enumerates as a generic HID
device with a simple one byte report and communicates with a simple PC
application that drives LEDs and reports the state of buttons on the board.


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

  Right click on the BSP project in the project explorer window click
  Build Configurations->Set Active->(see configuration in table below)
  repeat these steps for all the below projects as well.
  
  CDL
  LPCUSBlib
  Example_GenericHIDDevice

Configure MCU:

  Right click on the Example_GenericHIDDevice project in the project explorer
  window then click Properties->C/C++ Build->MCU settings->(see configuration in
  table below).

Configure the indexer:
   Click Window->Preferences->C/C++->Indexer->Use active build configuration

                                     BSP                 CDL           LPCUSBlib     Example_GenericHIDDevice    MCU
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
Open Project: To open this project go to Project-> Open Project... Go to the BSP
directory on click on the BSP.uvproj

Configure a Batch Build:
  Click on Project->Batch Build... expand the BSP project to display a list of
  project targets select the project target by checking the appropriate checkbox
 (see target list in table below) repeat these steps with the
 
  CDL
  LPCUSBlib_Device
  Example_GenericHIDDevice

                             BSP                      CDL     LPCUSBlib_Device GenericHIDDevice 
                          ==========               =========  ================ ================
LPC11U14 / MCB1000         MCB1000                  LPC11Uxx   LPC11Uxx_Device      MCB1000
LPC1768  / MCB1700         MCB1700                  LPC17xx    LPC17xx_Device       MCB1700
LPC1778  / EmbeddedArtists EAOEMBaseRevA_LPC177x_8x LPC177x_8x LPC177x_8x_Device    EAOEMBaseRevA_LPC177x_8x
LPC1850  / Hitex           HITEX1800                LPC18xx    LPC18xx_Device       HITEX1800
LPC4350  / Hitex           HITEX4300                LPC43xx    LPC43xx_Device       HITEX4300
LPC1830  / Xplorer         Xplorer                  LPC18xx    LPC18xx_Device       XPLORER1830
LPC4330  / Xplorer         Xplorer                  LPC43xx    LPC43xx_Device       XPLORER4330
LPC4330  / Element14       Xplorer                  LPC43xx    LPC43xx_Device       XPLORER4330

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
       This example does not light any LEDs on this board
       This example only uses SW6 to send reports to the PC
       USB1 is used in this example which cannot power this board.
       To power the board, use J32 (USB2 mini) or J24 (external power)

	
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

Use a PC running Windows XP, Vista or 7 connect the type-A end of the USB cable
that is connected to the board into one of the USB receptacles on the PC.

=================================
==                             ==
== Build and debug the example ==
==                             ==
=================================

LPCXpresso IDE
--------------

In the project explorer window of the IDE right click on the
Example_GenericHIDDevice project and select Build. Once the project has
completed building then right click on Example_GenericHIDDevice project and
select Debug As->C/C++ MCU Application. In the main window of the IDE click 
Run->Resume to start running the application

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
will enumerate on the PC as a generic HID device. You should see the device 
appear in the "Device Manager" under the "Human Interface Device".
If you right click on USB Input Device->Properties
a window will appear called "USB Input Device Properties". If you
select the "Details" tab you will see a "Properties" drop down, click on it and
select "Hardware Ids". You should see the below entries for Vendor Id and
Product Id.

USB\VID_1FC9&PID_0007&REV_0100
USB\VID_1FC9&PID_0007

This information should match the data in the "Device Descriptor Sturcture"
in the "Descriptors.c" file in the Example_GenericHIDDevice project directory.

Run the included PC application HIDClient.exe to send reports between the host
and device. 
Use the Device: drop down list box to select "LPCUSBlib Generic HID Demo"
Press buttons on the board and see check boxes become checked in the first row
Clieck the check boxes in the second row to light up LEDs on the board

