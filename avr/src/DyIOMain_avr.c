
#include "UserApp_avr.h"

BowlerPacket Packet;

void Server(){
	UserRun();
	// Run the Bowler Stack Namespace iteration of all async packets
	// Pass in  the function pointer to push the packets upstream
	RunNamespaceAsync((BowlerPacket *)&Packet,&avrAsyncCallbackPtr);
	Bowler_Server((BowlerPacket *) &Packet,true) ;
}

//#define analogTime  10
//	RunEveryData asyncSched = {0,analogTime};
void runDyIOMain(void){
	UCSR1B=0;
	UCSR1C=0;
	UCSR1A=0;
//
//	UCSR0B=0;
//	UCSR0C=0;
//	UCSR0A=0;
	startScheduler();
	AVR_Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1
	UserInit();// User code init
	setPrintLevelWarningPrint();
//	GetIOChannelCountFromPacket(&Packet);
//	FixPacket(&Packet);
//	printPacket(&Packet,WARN_PRINT);

	while (1){
		//Run from Interrupts only
		Server();

	}
}
