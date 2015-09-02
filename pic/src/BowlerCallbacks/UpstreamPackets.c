/**
 * @file UpstreamPackets.c
 *
 * Created on: Dec 4, 2010
 * @author hephaestus
 */


#include "UserApp.h"

BowlerPacket packetTemp;
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

//void PushAllAsync(){
//	SetColor(0,1,0);
//
//	GetAllChanelValueFromPacket(&packetTemp);
//	int i,packetIndex;
//	for(i=0;i<NUM_PINS;i++){
//		packetIndex = (i*4) +1;
//		if(GetChannelMode(i) == IS_SERVO){
//			//mask off the time value before sending upstream
//			set32bit(&packetTemp, get32bit(&packetTemp, packetIndex)&0x000000ff, packetIndex);
//		}
//	}
//
//	packetTemp.use.head.Method=BOWLER_ASYN;
//	Print_Level l = getPrintLevel();
//	setPrintLevelInfoPrint();
//	PutBowlerPacket(& packetTemp);
//	println_W("Sending All Async: ");printPacket(&packetTemp,WARN_PRINT);
//	setPrintLevel(l);
//}


void UpstreamPushPowerChange(uint8_t r0,uint8_t r1, uint16_t voltage, uint8_t override){
	//SetColor(0,1,0);
	packetTemp.use.head.RPC=GetRPCValue("_pwr");
	packetTemp.use.head.MessageID=3;
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.data[0]=r0;
	packetTemp.use.data[1]=r1;
	set16bit(&packetTemp,voltage,2);
	packetTemp.use.data[4]=override;
	packetTemp.use.head.DataLegnth=4+2+2+1;

	PutBowlerPacketLocal(& packetTemp);
	//printPacket(&packetTemp,WARN_PRINT);
}

void UpstreamPushSPIlStream(void){
	//SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.RPC=GetRPCValue("strm");
	packetTemp.use.head.MessageID=3;
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.data[0] = 0; //the SPI clock pin
	packetTemp.use.data[1]=GetSPIRxData(&packetTemp.use.data[2]);
	packetTemp.use.head.DataLegnth = 4+1+1+packetTemp.use.data[1];
	PutBowlerPacketLocal(& packetTemp);
	//printPacket(&packetTemp,WARN_PRINT);

}

void UpstreamPushSerialStream(void){
	//SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.RPC=GetRPCValue("strm");
	packetTemp.use.head.MessageID=3;
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.data[0] = 17; //the serial rx pin
	packetTemp.use.data[1]=GetSerialRxData(&packetTemp.use.data[2]);
	packetTemp.use.head.DataLegnth = 4+1+1+packetTemp.use.data[1];
	PutBowlerPacketLocal(& packetTemp);
	//printPacket(&packetTemp,WARN_PRINT);

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
	packet->use.head.DataLegnth=4+2+2+1;
}

void pushPPMPacket(void){
	//SetColor(0,1,0);
	GetPPMDataToPacket(& packetTemp);
	packetTemp.use.head.MessageID=45;

	packetTemp.use.head.Method=BOWLER_ASYN;
	PutBowlerPacketLocal(& packetTemp);
	//printPacket(&packetTemp,WARN_PRINT);
}


