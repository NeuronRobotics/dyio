/*
 * UserInit.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

//uint8_t InputState[NUM_PINS];

uint8_t SaveTheState = 0;

#define mInitSwitch()      (_TRISB0)=1;

const uint8_t MY_MAC_ADDRESS[] = {0x74, 0xf7, 0x26, 0x00, 0x00, 0x00};

extern MAC_ADDR MyMAC __attribute__((section(".scs_global_var")));
char macStr[13];

#if defined(ROBOSUB_DEMO)
//char * dev = "AHD Wave";
#else
char * dev = "DyIO v1.0";
#endif

void hardwareInit() {


    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig((80000000L), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    SYSTEMConfigPerformance(80000000);
    CHECONbits.PREFEN = 0;


    int j = 0, i = 0;
#if defined(PROGRAMMER_DEBUG)
    //FlashSwitchMemoryToBootloader();
#endif
    for (i = 0; i < 6; i++) {
        MyMAC.v[i] = MY_MAC_ADDRESS[i];
    }
    StartCritical();
    println_I("Getting MAC from flash");
    enableFlashStorage(true);
    FlashGetMac(MyMAC.v);


    for (i = 0; i < 6; i++) {
        macStr[j++] = GetHighNib(MyMAC.v[i]);
        macStr[j++] = GetLowNib(MyMAC.v[i]);
    }
    macStr[12] = 0;
    //println_I("MAC address is =");
    print_I(macStr);

    Pic32_Bowler_HAL_Init();
    usb_CDC_Serial_Init(dev, macStr, 0x04D8, 0x3742);
    InitLEDS();
    SetColor(0, 0, 1);

    mInitSwitch();


    //Must initialize IO before hardware
    InitPins();
    //println_I("Adding IO Namespace");
    addNamespaceToList( get_bcsIoNamespace());
    //println_I("Adding IO.Setmode Namespace");
    addNamespaceToList(get_bcsIoSetmodeNamespace());
    //println_I("Adding DyIO Namespace");
    addNamespaceToList(get_neuronRoboticsDyIONamespace());
    //println_I("Adding PID Namespace");
    addNamespaceToList( getBcsPidNamespace());
    //println_I("Adding DyIO PID Namespace");
    addNamespaceToList( get_bcsPidDypidNamespace());
    //println_I("Adding Safe Namespace");
    addNamespaceToList((NAMESPACE_LIST *) get_bcsSafeNamespace());


    Init_FLAG_BUSY_ASYNC();
    //InitCTS_RTS_HO();

    //AVR Reset pin
    InitAVR_RST();
    HoldAVRReset();

    //ConfigUARTOpenCollector();
    ConfigUARTRXTristate();

    //Starts Timer 3
    InitCounterPins();
    InitADC();


    uint8_t rev [] = {MAJOR_REV, MINOR_REV, FIRMWARE_VERSION};
    FlashSetFwRev(rev);

    //Starts co-proc uart
    initCoProcCom();

    EndCritical();

    //	initBluetooth();
    //	if(!hasBluetooth()){
    //		Pic32UARTSetBaud( 115200 );
    //	}


}

void UserInit(void) {
    //setPrintStream(&USBPutArray);
    setPrintLevelInfoPrint();
    //println_I("\n\nStarting PIC initialization");
    //DelayMs(1000);
    hardwareInit();
    //println_I("Hardware Init done");

    ReleaseAVRReset();



    CheckRev();

    LoadEEstore();

    LoadDefaultValues();


    InitPID();

    UpdateAVRLED();


    lockServos();
    setPrintLevelInfoPrint();

    boolean brown = getEEBrownOutDetect();
    setCoProcBrownOutMode(brown);
    setBrownOutDetect(brown);


    clearPrint();
    //println_I("###Starting PIC In Debug Mode###\n"); // All printfDEBUG functions do not need to be removed from code if debug is disabled
    //DelayMs(1000);
    setPrintLevelWarningPrint();
    //println_E("Error level printing");
    //println_W("Warning level printing");
    //println_I("Info level printing");
}

