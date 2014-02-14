
#include "Bowler/Bowler.h"
#include "DyIO/DyIO_def.h"

void buttonCheck(BYTE code){
//	StartCritical();
//	EndCritical();
	if (_RB0==1){
		p_int_E(code);print_E(" Reset Button Pressed from loop");
		SetColor(1,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}
}

static BowlerPacket Packet;


void MyServer(){
	// Run the Bowler Stack Namespace iteration of all async packets
	// Pass in  the function pointer to push the packets upstream

	RunNamespaceAsync(&Packet,&PutBowlerPacket);
	Bowler_Server((BowlerPacket *) &Packet, FALSE);

}

void runDyIOMain(void){
	startScheduler();
	Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

	UserInit();// User code init
	while (1){
		MyServer();
		buttonCheck(0);
	}
}


