
#include "Bowler/Bowler.h"
#include "DyIO/DyIO_def.h"

void buttonCheck(BYTE code){
//	StartCritical();
//	EndCritical();
	if (_RB0==1){
		p_ul_E(code);print_E(" Reset Button Pressed from loop");
		SetColor(1,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}
}
#if defined(__AVR_ATmega324P__)
	static BowlerPacketMini Packet;
#else
	static BowlerPacket Packet;
#endif

void MyServer(){
	Bowler_Server((BowlerPacket *) &Packet, FALSE);
}

void runDyIOMain(void){
	startScheduler();
	Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

	UserInit();// User code init
	while (1){
		UserRun();
		MyServer();
		buttonCheck(0);
	}
}


