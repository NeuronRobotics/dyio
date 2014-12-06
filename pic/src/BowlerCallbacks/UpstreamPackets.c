/**
 * @file UpstreamPackets.c
 *
 * Created on: Dec 4, 2010
 * @author hephaestus
 */


#include "UserApp.h"

BowlerPacket packetTemp;
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

//void pushDummy(uint8_t numData){
//	LoadCorePacket(& packetTemp);
//	packetTemp.use.head.Method=BOWLER_ASYN;
//	packetTemp.use.head.RPC=GetRPCValue("test");
//	packetTemp.use.head.DataLegnth=4+numData;
//	int i;
//	for(i=0;i<numData;i++){
//		packetTemp.use.data[i]=numData;
//	}
//	Print_Level l = getPrintLevel();
//	setPrintLevelInfoPrint();
//	PutBowlerPacket(& packetTemp);
//	setPrintLevel(l);
//}

void PushAllAsync(){
	SetColor(0,1,0);

	GetAllChanelValueFromPacket(&packetTemp);
	int i,packetIndex;
	for(i=0;i<NUM_PINS;i++){
		packetIndex = (i*4) +1;
		if(GetChannelMode(i) == IS_SERVO){
			//mask off the time value before sending upstream
			set32bit(&packetTemp, get32bit(&packetTemp, packetIndex)&0x000000ff, packetIndex);
		}
	}

	packetTemp.use.head.Method=BOWLER_ASYN;
	Print_Level l = getPrintLevel();
	setPrintLevelInfoPrint();
	PutBowlerPacket(& packetTemp);
	println_W("Sending All Async: ");printPacket(&packetTemp,WARN_PRINT);
	setPrintLevel(l);
}
//void PushCounterChange(uint8_t pin,int64_t state){
//	SetColor(0,1,0);
//	INT32_UNION s;
//	s.Val= state;
//	LoadCorePacket(& packetTemp);
//	packetTemp.use.head.Method=BOWLER_ASYN;
//	packetTemp.use.head.RPC=GetRPCValue("gchv");
//	packetTemp.use.data[0]=pin;
//	packetTemp.use.data[1]=s.byte.FB;
//	packetTemp.use.data[2]=s.byte.TB;
//	packetTemp.use.data[3]=s.byte.SB;
//	packetTemp.use.data[4]=s.byte.LB;
//	packetTemp.use.head.DataLegnth=9;
//	PutBowlerPacket(& packetTemp);
//}
//void PushADCval(uint8_t pin,uint16_t val){
//	if(val>1024 || val<0)
//		return;
//	UINT16_UNION an;
//	an.Val=val;
//	SetColor(0,1,0);
//	LoadCorePacket(& packetTemp);
//	packetTemp.use.head.Method=BOWLER_ASYN;
//	packetTemp.use.head.RPC=GetRPCValue("gchv");
//	packetTemp.use.data[0]=pin;
//	packetTemp.use.data[1]=an.byte.SB;
//	packetTemp.use.data[2]=an.byte.LB;
//	packetTemp.use.head.DataLegnth=7;
//	PutBowlerPacket(& packetTemp);
//}
//void PushDIval(uint8_t pin,uint8_t val){
//	if(val>1 || val<0)
//		return;
//	SetColor(0,1,0);
//	LoadCorePacket(& packetTemp);
//	packetTemp.use.head.Method=BOWLER_ASYN;
//	packetTemp.use.head.RPC=GetRPCValue("gchv");
//	packetTemp.use.data[0]=pin;
//	packetTemp.use.data[1]=val;
//	packetTemp.use.head.DataLegnth=6;
//	PutBowlerPacket(& packetTemp);
//}

void UpstreamPushPowerChange(void){
	SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	POWER(& packetTemp);
	packetTemp.use.head.MessageID=3;
	packetTemp.use.head.Method=BOWLER_ASYN;
	PutBowlerPacket(& packetTemp);
}

void UpstreamPushSPIlStream(void){
	SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.RPC=GetRPCValue("strm");
	packetTemp.use.head.MessageID=3;
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.data[0] = 0; //the SPI clock pin
	packetTemp.use.data[1]=GetSPIRxData(&packetTemp.use.data[2]);
	packetTemp.use.head.DataLegnth = 4+1+1+packetTemp.use.data[1];
	PutBowlerPacket(& packetTemp);
}

void UpstreamPushSerialStream(void){
	SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.RPC=GetRPCValue("strm");
	packetTemp.use.head.MessageID=3;
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.data[0] = 17; //the serial rx pin
	packetTemp.use.data[1]=GetSerialRxData(&packetTemp.use.data[2]);
	packetTemp.use.head.DataLegnth = 4+1+1+packetTemp.use.data[1];
	PutBowlerPacket(& packetTemp);
}

void POWER(BowlerPacket * packet){

	UINT16_UNION raw;
	packet->use.head.Method=BOWLER_GET;
	packet->use.head.RPC=GetRPCValue("_pwr");
	packet->use.data[0]=isRegulated_0();
	packet->use.data[1]=isRegulated_1();
	raw.Val=(uint16_t)(GetRawVoltage());
	packet->use.data[2]=raw.byte.SB;
	packet->use.data[3]=raw.byte.LB;
	packet->use.data[4]=getPowerOverRide();
	packet->use.head.DataLegnth=9;
}

void pushPPMPacket(void){
	SetColor(0,1,0);
	GetPPMDataToPacket(& packetTemp);
	packetTemp.use.head.MessageID=45;

	packetTemp.use.head.Method=BOWLER_ASYN;
	PutBowlerPacket(& packetTemp);
}


