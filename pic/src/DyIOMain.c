
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
 boolean pushing = false;

 boolean PutBowlerPacketLocal(BowlerPacket * Packet){

	 pushing = true;
	 //StartCritical();
         SetRed(1);
	 boolean ret = PutBowlerPacket(Packet);
	 //EndCritical();
         SetRed(0);
	 pushing = false;
         return ret;
 }
void runDyIOMain(void){
	startScheduler();
	Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

	UserInit();// User code init
	//println_I("Main Loop Start");

	//kick off packet processor timer
	OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_64 , 100);
	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_5);

	while (1){
		RunNamespaceAsync(&Packet,&PutBowlerPacketLocal);
		buttonCheck(0);
	}
}

void __ISR(_TIMER_4_VECTOR, ipl5) _Timer4Handler(void)
{
	//shut off the timer to avoid process recoursion
	ConfigIntTimer4(T4_INT_OFF);
	mT4ClearIntFlag();
	//re-enable interrupts so the stack can function if a long process takes place
	EndCritical();
	//button check in the timer, acts as a psudo-watchdog
	if(_RB0==1){
		SetColor(0,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}
	if(pushing == false){
		// Run the Bowler Stack Namespace iteration of all async packets
		// Pass in  the function pointer to push the packets upstream
		boolean back = GetBowlerPacket_arch(&Packet);
		if (back) {
			SetGreen(1);
			if (process(&Packet)) {
				//Packet found, sending
				PutBowlerPacket(&Packet);
				SetGreen(0);
			}
		}//Have a packet
	}
	OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_64 , 100);
	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_5);
}


