
#include "UserApp.h"

void buttonCheck(uint8_t code){
	if (_RB0==1){
		p_int_E(code);print_E(" Reset");
		SetColor(1,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}

}

 BowlerPacket Packet;


void runDyIOMain(void){
	startScheduler();
	Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

	UserInit();// User code init
	//println_I("Main Loop Start");

	OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_256, (0x1000/10 ));
	ConfigIntTimer3(T4_INT_ON | T4_INT_PRIOR_5);

	while (1){

		RunNamespaceAsync(&Packet,&PutBowlerPacket);
		buttonCheck(0);
	}
}

void __ISR(_TIMER_4_VECTOR, ipl5) _Timer3Handler(void)
{
	//StartCritical();
	ConfigIntTimer4(T4_INT_OFF);
	mT4ClearIntFlag();
	// Run the Bowler Stack Namespace iteration of all async packets
	// Pass in  the function pointer to push the packets upstream
	Bowler_Server((BowlerPacket *) &Packet, false) ;
	buttonCheck(99);
	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_5);
	//EndCritical();
}


