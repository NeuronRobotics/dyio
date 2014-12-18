
#include "UserApp.h"
boolean serverRecursionCheck = false;
void buttonCheck(uint8_t code){

//	StartCritical();
//	EndCritical();
	if (_RB0==1){
		p_int_E(code);print_E(" Reset");
		SetColor(1,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}
	if(serverRecursionCheck == true){
		//println_E("Server recursion detected");
		return;
	}
	serverRecursionCheck = true;
	MyServer();
	serverRecursionCheck = false;
}

 BowlerPacket Packet;


void MyServer(){

	//println_I("Main Loop 2");
	Bowler_Server((BowlerPacket *) &Packet, false) ;
	//println_I("Main Loop 3");
}

void runDyIOMain(void){
	startScheduler();
	Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

	UserInit();// User code init
	//println_I("Main Loop Start");
	while (1){
		MyServer();
		// Run the Bowler Stack Namespace iteration of all async packets
		// Pass in  the function pointer to push the packets upstream


		RunNamespaceAsync(&Packet,&PutBowlerPacket);
		buttonCheck(0);
	}
}


