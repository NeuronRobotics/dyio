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

uint8_t MY_MAC_ADDRESS[] = {0x74, 0xf7, 0x26, 0x00, 0x00, 0x00};
char					LockCode[5];
char 					Name[17];
char defaultName[] = "DyIO Module";
char defaultlock[] = "0000";

extern MAC_ADDR MyMAC __attribute__((section(".scs_global_var")));
char macStr[13];

#if defined(ROBOSUB_DEMO)
//char * dev = "AHD Wave";
#else
char  dev [] = "DyIO v1.0";
#endif

uint8_t rev [] = {MAJOR_REV, MINOR_REV, FIRMWARE_VERSION};



void hardwareInit() {


    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig((80000000L), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    SYSTEMConfigPerformance(80000000);
    CHECONbits.PREFEN = 0;


    int j = 0, i = 0;

    for (i = 0; i < 6; i++) {
        MyMAC.v[i] = MY_MAC_ADDRESS[i];
    }
    StartCritical();

    println_I("MAC");
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

    //AVR Reset pin
    InitAVR_RST();
    HoldAVRReset();
    //AVR must be running before pin states can be synced in the pin initialization
    ReleaseAVRReset();
    //Starts co-proc uart
    initCoProcCom();
    
    InitPinFunction();
    //Must initialize IO before hardware
    LoadDefaultValues();
    //println_W("Pin States");
    SyncModes();
    //println_I("Modes synced, initializing channels");
    initAdvancedAsync();

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

    //ConfigUARTOpenCollector();
    ConfigUARTRXTristate();

    //Starts Timer 3
    InitCounterPins();
    InitADC();



    //SetFwRev(rev);



    GetName(Name);
    if(Name[0]==0xff){
            for(i=0;i<17;i++){
                    Name[i]=defaultName[i] ;
            }
            SetName(Name);
            GetName(Name);
    }

    if (!GetLockCode(LockCode)){
            for(i=0;i<4;i++){
                LockCode[i] = defaultlock[i];
            }
            SetLockCode(LockCode);
    }

    EndCritical();

//	initBluetooth();
//	if(!hasBluetooth()){
//		Pic32UARTSetBaud( 115200 );
//	}

    boolean defaultmac=true;
    for (i = 0; (i < 6) && defaultmac; i++) {
    	if(MyMAC.v[i] != MY_MAC_ADDRESS[i]){
    		defaultmac = false;
    	}
    }
#if !defined(__DEBUG)
    if(defaultmac){
    	srand((unsigned) GetRawVoltage());// random seed from the air

    	MyMAC.v[3] = MINOR_REV;
    	MyMAC.v[4] = FIRMWARE_VERSION;
    	MyMAC.v[5] = rand() % 255;
    	FlashSetMac(MyMAC.v);
		U1CON = 0x0000;
		DelayMs(100);
    	Reset();
    }
#endif
}

void UserInit(void) {
    //setPrintStream(&USBPutArray);
    clearPrint();
    setPrintLevelInfoPrint();
    println_I("Start PIC");
    //DelayMs(1000);
    hardwareInit();
    //println_I("Hardware Init done");

    InitializeDyIODataTableManager();

    CheckRev();

    LoadEEstore();


    

    UpdateAVRLED();


    lockServos();
    //setPrintLevelInfoPrint();

    boolean brown = getEEBrownOutDetect() ? true:false;
    setBrownOutDetect(brown);

    //Data table needs to be synced before the PID can init properly
    SyncDataTable();
    InitPID();

    
    //println_I("###Starting PIC In Debug Mode###\n"); // All printfDEBUG functions do not need to be removed from code if debug is disabled
    //DelayMs(1000);
    setPrintLevelWarningPrint();
    //println_E("Error level printing");
    //println_W("Warning level printing");
    //println_I("Info level printing");
}

