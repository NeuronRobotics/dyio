/*
 * UserInit.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

//uint8_t InputState[NUM_PINS];

uint8_t SaveTheState=0;

#define mInitSwitch()      (_TRISB0)=1;

const uint8_t MY_MAC_ADDRESS[]={0x74,0xf7,0x26,0x01,0x01,0x01};

extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

void hardwareInit(){
	StartCritical();
	println_I("Getting MAC from flash");
	FlashGetMac(MyMAC.v);
	char macStr[13];
	int j=0,i=0;
	for (i=0;i<6;i++){
		macStr[j++]=GetHighNib(MyMAC.v[i]);
		macStr[j++]=GetLowNib(MyMAC.v[i]);
	}
	macStr[12]=0;
	println_I("MAC address is =");
	print_I(macStr);
#if defined(ROBOSUB_DEMO)
	//char * dev = "AHD Wave";
#else
	char * dev = "DyIO v.3";
#endif
	Pic32_Bowler_HAL_Init();
	usb_CDC_Serial_Init(dev,macStr,0x04D8,0x3742);

	mInitSwitch();

	for (i=0;i<6;i++){
		MyMAC.v[i]= MY_MAC_ADDRESS[i];
	}
	//Must initialize IO before hardware
	InitPins();
	println_I("Adding IO Namespace");
	addNamespaceToList((NAMESPACE_LIST * )get_bcsIoNamespace());
	println_I("Adding IO.Setmode Namespace");
	addNamespaceToList((NAMESPACE_LIST * )get_bcsIoSetmodeNamespace());
	println_I("Adding DyIO Namespace");
	addNamespaceToList((NAMESPACE_LIST * )get_neuronRoboticsDyIONamespace());
	println_I("Adding PID Namespace");
	addNamespaceToList((NAMESPACE_LIST * )getBcsPidNamespace());
	println_I("Adding DyIO PID Namespace");
	addNamespaceToList((NAMESPACE_LIST * )get_bcsPidDypidNamespace());
	println_I("Adding Safe Namespace");
	addNamespaceToList((NAMESPACE_LIST * )get_bcsSafeNamespace());


	Init_FLAG_BUSY_ASYNC();
	//InitCTS_RTS_HO();

	//AVR Reset pin
	InitAVR_RST();
	HoldAVRReset();

	//ConfigUARTOpenCollector();
	ConfigUARTRXTristate();


	InitLEDS();
	SetColor(0,0,1);
	//Starts Timer 3
	InitCounterPins();
	InitADC();


	uint8_t rev [] = {MAJOR_REV,MINOR_REV,FIRMWARE_VERSION};
	FlashSetFwRev(rev);

	//Starts co-proc uart
	initCoProcCom();

	EndCritical();
	INTEnableSystemMultiVectoredInt();

//	initBluetooth();
//	if(!hasBluetooth()){
//		Pic32UARTSetBaud( 115200 );
//	}

}

void UserInit(void){
	//setPrintStream(&USBPutArray);
	setPrintLevelInfoPrint();
	println_I("\n\nStarting PIC initialization");
	//DelayMs(1000);
	hardwareInit();
	println_I("Hardware Init done");

	ReleaseAVRReset();



	CheckRev();

	LoadEEstore();

	LoadDefaultValues();

	CartesianControllerInit();

	InitPID();

	UpdateAVRLED();


	lockServos();
	setPrintLevelInfoPrint();

	boolean brown = getEEBrownOutDetect();
	setCoProcBrownOutMode(brown);
	setBrownOutDetect(brown);

        clearPrint();
	println_I("###Starting PIC In Debug Mode###\n");// All printfDEBUG functions do not need to be removed from code if debug is disabled
	//DelayMs(1000);
	setPrintLevelWarningPrint();
	println_E("Error level printing");
	println_W("Warning level printing");
	println_I("Info level printing");
}

