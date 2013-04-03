
#include "UserApp_avr.h"

static BowlerPacketMini Packet;

void server(){
	// Run the Bowler Stack Namespace iteration of all async packets
	// Pass in  the function pointer to push the packets upstream
	RunNamespaceAsync((BowlerPacket *)&Packet,&avrAsyncCallbackPtr);
	Bowler_Server((BowlerPacket *) &Packet,TRUE);
}

//#define analogTime  10
//static 	RunEveryData asyncSched = {0,analogTime};
void runDyIOMain(void){
	startScheduler();
	AVR_Bowler_HAL_Init();
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1
	UserInit();// User code init
	println_I("Stack initialized");

	while (1){

		//start =  getMs();
		UserRun();
		server();

//		//float one =  getMs();
//		if(FlagAsync == FLAG_OK ){
//			if(checkDigital())
//				server();
//		}else{
//			//println_I("Skipping D async");
//		}
//		//float two =  getMs();
//		server();
//		//float three =  getMs();
//		if(FlagAsync == FLAG_OK ){
//			if (RunEvery(&asyncSched)>0){
//				if(checkAnalog())
//					server();
//			}else{
//				now = getMs();
//				if(!((asyncSched.MsTime >= 0) && (asyncSched.MsTime <= now))){
//#if ! defined(__AVR_ATmega324P__)
//					println_E("Reseting async time, was=");p_fl_E(asyncSched.MsTime);print_E(" is=");p_fl_E(now);
//					println_E("Timer in ticks:");p_sl_E(GetTimeTicks());
//#endif
//					asyncSched.setPoint = analogTime;
//					asyncSched.MsTime=now;
//					server();
//				}
//
//			}
//		}else{
//			//println_I("Skipping A async");
//		}
//		//float four =  getMs();
//		server();
//		float five =  getMs();
//		println_I("TOTAL ");p_fl_I(start-five);
//		println_I("\t\tDone servo ");p_fl_I(start-one);
//		println_I("\t\tDone Dig ");p_fl_I(one-two);
//		println_I("\t\tDone Server 1");p_fl_I(two-three);
//		println_I("\t\tDone Analog ");p_fl_I(three-four);
//		println_I("\t\tDone Server 2");p_fl_I(four-five);

	}
}
