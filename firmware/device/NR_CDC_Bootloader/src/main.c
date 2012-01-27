
#define MAINAPP

#include "main.h"

#include "DyIO/DyIO_def.h"

const unsigned char bootloaderNSName[] = "neuronrobotics.bootloader.*;0.3;;\0";

const unsigned char infoNSName[] = "neuronrobotics.dyio._rev;0.3;;\0";



void BlinkUSBStatus(void);
BOOL DebugFlag=TRUE;
//unsigned int __attribute__((section("boot_software_key_sec,\"aw\",@nobits#"))) SoftwareKey;
BOOL resetFlag;

typedef enum _Myexcep_code{
    EXCEP_IRQ = 0,          // interrupt
    EXCEP_AdEL = 4,         // address error exception (load or ifetch)
    EXCEP_AdES,             // address error exception (store)
    EXCEP_IBE,              // bus error (ifetch)
    EXCEP_DBE,              // bus error (load/store)
    EXCEP_Sys,              // syscall
    EXCEP_Bp,               // breakpoint
    EXCEP_RI,               // reserved instruction
    EXCEP_CpU,              // coprocessor unusable
    EXCEP_Overflow,         // arithmetic overflow
    EXCEP_Trap,             // trap (possible divide by zero)
    EXCEP_IS1 = 16,         // implementation specfic 1
    EXCEP_CEU,              // CorExtend Unuseable
    EXCEP_C2E               // coprocessor 2
} Myexcep_code;

void _general_exception_handler(unsigned cause, unsigned status){

	//printfDEBUG("#@#Exception! Status: ");
	//printfDEBUG_UL(cause);
        Myexcep_code code = (status & 0x0000007C) >> 2;;
	switch(code){
            case EXCEP_AdEL:
                println("address error exception (load or ifetch)");
                break;
            case EXCEP_AdES:
                println("address error exception (store)");
                break;
            case EXCEP_Bp:
                println("breakpoint");
                return;
            case EXCEP_C2E:
                println("coprocessor 2");
                break;
            case EXCEP_CEU:
                println("CorExtend Unuseable");
                break;
            case EXCEP_CpU:
                println("coprocessor unusable");
                break;
            case EXCEP_DBE:
                println("bus error (load/store)");
                break;
            case EXCEP_IBE:
                println("bus error (ifetch)");
                break;
            case EXCEP_IRQ:
                println("unhandled interrupt");
                break;
            case EXCEP_IS1:
                println("implementation specfic 1");
                break;
            case EXCEP_Overflow:
                println("arithmetic overflow");
                break;
            case EXCEP_RI:
                println("reserved instruction");
                break;
            case EXCEP_Sys:
                println("syscall");
                break;
            case EXCEP_Trap:
                println("trap (possible divide by zero)");
                break;
            default:
		break;
	}
        initLed();
	setLed(1,0,0);
	initButton();
	while(1){
		if(isPressed())
			Reset();
		setLed(1,0,0);
		DelayMs(1000);
		if(isPressed())
			Reset();
		setLed(1,0,1);
		DelayMs(200);
	}
}
static BowlerPacket Packet;
int main(void){
	initLed();
	setLed(1,1,1);
	initButton();
	int timeout=0;
	while (isPressed()){
		Delay10us(1);
		timeout ++;
		if (timeout >= 10000){
			BlinkUSBStatus();
		}
	}
	setLed(0,0,0);
	if ((!isPressed()&&(timeout < 10000))){

		void (*fptr)(void);
		fptr = (void (*)(void))StartAppVectVirtual;
		// If there IS no real program to execute, then fall through to the bootloader
		if (*(int *)StartAppVectVirtual != 0xFFFFFFFF)
		{
			StopSPI();
			fptr();
			while(1);
		}
	}

	InitializeSystem();

	resetFlag=FALSE;
    while(1) {
    	if(getVendorCode() == 0x1E){
    		BlinkUSBStatus();
    	}else{
    		setLed(1,0,0);
    	}
    	Bowler_Server(&Packet, TRUE);
        if((isPressed()||resetFlag)){
			U1CON = 0x0000;
			DelayMs(100);
			Reset();
        }
    }//end while
}
static BYTE avrID[7];
void InitializeSystem(void)
{
	Bowler_Init();
	//println("Stack initialized");
#if !defined(MAJOR_REV)
	#define MAJOR_REV			3
	#define MINOR_REV			0
	#define FIRMWARE_VERSION	1
#endif
	BYTE rev[] = {MAJOR_REV,MINOR_REV,FIRMWARE_VERSION};
	//println("Seting BL version");
	FlashSetBlRev(rev);

	//println("Adding Namespaces ");
	AddNamespace(sizeof(bootloaderNSName), bootloaderNSName);
	AddNamespace(sizeof(infoNSName), infoNSName);

	//println("Namespaces added");

	char * dev = "NR CDC Bootloader";
	char * ser = "FF00FF00FF00";
	usb_CDC_Serial_Init(dev,ser,0x04D8,0x0001);

#if defined(DYIO)
	InitSPI();
	InitAVR_RST();

	setLed(1,0,1);
	programMode();
	writeLowFuse();
	writeHighFuse();
	writeExtendedFuse();
	GetAVRid(avrID);

	ReleaseAVRReset();
	DelayMs(10);
	HoldAVRReset();
	GetAVRid(avrID);
#endif
	setMethodCallback(BOWLER_GET,UserGetRPCs);
	setMethodCallback(BOWLER_POST,UserPostRPCs);
	setMethodCallback(BOWLER_CRIT,UserCriticalRPCs);


	//printfDEBUG("#Starting...");

	//printfDEBUG("AVR ID string: ");
	//printfDEBUG_NNL(avrID);

}

BYTE core0str[]="\npic32mx440f128h";
BYTE core1str[]="\navr_atmegaXX4p_";
BYTE UserGetRPCs(BowlerPacket *Packet){
	int i;
	int offset=0;
	BYTE rev[3];
	switch (Packet->use.head.RPC){
	case BLID:
		Packet->use.head.Method=BOWLER_POST;
		for (i=0;i<sizeof(core0str);i++){
			Packet->use.data[i]=core0str[i];
		}
		offset = sizeof(core0str);
		for (i=0;i<sizeof(core1str);i++){
			Packet->use.data[i+offset]=core1str[i];
		}
		offset= sizeof(core0str)+sizeof(core1str);
		for (i=0;i<6;i++){
			Packet->use.data[i+offset-1]=avrID[i];
		}
		Packet->use.head.DataLegnth=sizeof(core0str)+sizeof(core1str)+6+4;
		break;
	case _REV:
		FlashGetFwRev(rev);
		for (i=0;i<3;i++){
			Packet->use.data[i]=rev[i];
		}
		FlashGetBlRev(rev);
		for (i=0;i<3;i++){
			Packet->use.data[i+3]=rev[i];
		}
		Packet->use.head.DataLegnth=4+6;
		break;
	}
	return TRUE;
}
BYTE UserPostRPCs(BowlerPacket *Packet){
	return 0;
}
BYTE UserCriticalRPCs(BowlerPacket *Packet){

	switch (Packet->use.head.RPC){

	case PROG:
		if (Packet->use.data[0]==0){
			writeLine(Packet);
		}else{
#if !defined(DYIO)
			ERR(Packet,0,1);
			break;
#endif
		}
		if (Packet->use.data[0]==1){
			avrSPIProg(Packet);
		}
		READY(Packet,0,0);
		break;
	case ERFL:
		if (Packet->use.data[0]==0){
			eraseFlash();
		}else{
#if !defined(DYIO)
			ERR(Packet,0,2);
			break;
#endif
		}
		if (Packet->use.data[0]==1){
			eraseAVR();
		}
		READY(Packet,0,1);
		//printfDEBUG("#Erasing device");
		break;
	case REST:
		//printfDEBUG("#Resetting device");
		resetFlag=TRUE;
		READY(Packet,0,3);
	}
	return TRUE;
}


