
#include "UserApp.h"

void buttonCheck(uint8_t code){
//	if (_RB0==1){
//		p_int_E(code);print_E(" Reset");
//		SetColor(1,1,1);
//		U1CON = 0x0000;
//		DelayMs(100);
//		Reset();
//	}

}

 BowlerPacket Packet;

 boolean PutBowlerPacketLocal(BowlerPacket * Packet){
	 StartCritical();
	 PutBowlerPacket(Packet);
	 EndCritical();
 }
void runDyIOMain(void){
	startScheduler();
	Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

	UserInit();// User code init
	//println_I("Main Loop Start");

	OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_16, 100);
	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_5);

	while (1){
		//_Timer4Handler() ;
		RunNamespaceAsync(&Packet,&PutBowlerPacketLocal);
		buttonCheck(0);
	}
}

void __ISR(_TIMER_4_VECTOR, ipl5) _Timer4Handler(void)
{
	//StartCritical();
	ConfigIntTimer4(T4_INT_OFF);
	mT4ClearIntFlag();
	while (_RB0==1){
		SetColor(0,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}
	// Run the Bowler Stack Namespace iteration of all async packets
	// Pass in  the function pointer to push the packets upstream
    boolean back = GetBowlerPacket_arch(&Packet);
    if (back) {
        SetColor(0, 1, 0);
        if (process(&Packet)) {
            //Packet found, sending
            PutBowlerPacket(&Packet);
            if (Packet.use.head.RPC != GetRPCValue("_pwr") &&
                    Packet.use.head.RPC != GetRPCValue("_png")&&
                    Packet.use.head.RPC != GetRPCValue("_rpc") &&
                                        Packet.use.head.RPC != GetRPCValue("_nms") &&
                                        Packet.use.head.RPC != GetRPCValue("args")
                    ) {//Ignore Power Packet
                println("Response:", INFO_PRINT);
                printPacket(&Packet, INFO_PRINT);
            }
            SetColor(0, 0, 1);
        }
    }//Have a packet

	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_5);
	//EndCritical();
}


