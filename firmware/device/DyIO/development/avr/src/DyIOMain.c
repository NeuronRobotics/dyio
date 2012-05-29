
#include "UserApp.h"

#if defined(__AVR_ATmega324P__)
	static BowlerPacketMini Packet;
#else
	static BowlerPacket Packet;
#endif
void server(){
	Bowler_Server((BowlerPacket *) &Packet,TRUE);
}

#define analogTime  50
static 	RunEveryData asyncSched = {0,analogTime};
void runDyIOMain(void){

	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1
	//println_I("Stack initialized");
	UserInit();// User code init
	//int i;

	float now;
	while (1){
		UserRun();

		if(FlagAsync == FLAG_OK ){
			if(checkDigital())
				server();
		}else{
			//println_I("Skipping D async");
		}
		server();
		if(FlagAsync == FLAG_OK ){
			if (RunEvery(&asyncSched)>0){
				if(checkAnalog())
					server();
			}else{
				now = getMs();
				if(!((asyncSched.MsTime >= 0) && (asyncSched.MsTime <= now))){
#if ! defined(__AVR_ATmega324P__)
					println_E("Reseting async time, was=");p_fl_E(asyncSched.MsTime);print_E(" is=");p_fl_E(now);
					println_E("Timer in ticks:");p_sl_E(GetTimeTicks());
#endif
					asyncSched.setPoint = analogTime;
					asyncSched.MsTime=now;
					server();
				}

			}
		}else{
			//println_I("Skipping A async");
		}
		server();

	}
}
