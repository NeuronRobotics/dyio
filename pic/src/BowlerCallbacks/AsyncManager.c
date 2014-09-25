/*
 * AsyncManager.c
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

//extern DATA_STRUCT DATA;
#define ADCINIT 0xFFFF
//void runAsyncIO();
//boolean isInit=false;
//AdvancedAsyncData asyncData[NUM_PINS];

void ProcessAsyncData(BowlerPacket * Packet){
	//println_I("**Got Async Packet**");
	//printPacket(Packet,INFO_PRINT);

	Print_Level l = getPrintLevel();
	setPrintLevelInfoPrint();

	if (Packet->use.head.RPC==GetRPCValue("gchv")){
		uint8_t pin = Packet->use.data[0];
		uint8_t mode = GetChannelMode(pin);
		if(mode == IS_ANALOG_IN ){
			UINT16_UNION ana;
			ana.byte.SB = Packet->use.data[1];
			ana.byte.LB = Packet->use.data[2];
			//ADC_val[pin-8]=ana.Val;
			if(ana.Val>=0 && ana.Val<1024)
				SetValFromAsync(pin,ana.Val);//asyncData[pin].currentVal=ana.Val;
			println_W("***Setting analog value: ");p_int_W(pin);print_W(", ");p_int_W(ana.Val);
		}
		else if((mode == IS_DI) || (mode == IS_COUNTER_INPUT_HOME)|| (mode == IS_COUNTER_OUTPUT_HOME) || mode == IS_SERVO){
			//DIG_val[pin]=Packet->use.data[1];
			SetValFromAsync(pin,Packet->use.data[1]);//asyncData[pin].currentVal=Packet->use.data[1];
			println_I("***Setting digital value: ");p_int_I(pin);print_I(", ");p_int_I(Packet->use.data[1]);//printStream(DIG_val,NUM_PINS);
		}else {
			if(IsAsync(pin)){
				println_I("Sending async packet, not digital or analog");
				PutBowlerPacket(Packet);
			}
		}
	}else if (Packet->use.head.RPC==GetRPCValue("aasn")){
		int i;
		for(i=0;i<8;i++){
			uint8_t pin = i+8;
			uint8_t mode = GetChannelMode(pin);
			if(mode == IS_ANALOG_IN ){
				UINT16_UNION ana;
				ana.byte.SB = Packet->use.data[i*2];
				ana.byte.LB = Packet->use.data[(i*2)+1];
				//ADC_val[pin-8]=ana.Val
				if(ana.Val>=0 && ana.Val<1024);
					SetValFromAsync(pin,ana.Val);//asyncData[pin].currentVal=ana.Val;
			}
		}
	}else if (Packet->use.head.RPC==GetRPCValue("dasn")){
		int i;
		for(i=0;i<GetNumberOfIOChannels();i++){
			uint8_t mode = GetChannelMode(i);
			if((mode == IS_DI) || (mode == IS_COUNTER_INPUT_HOME)|| (mode == IS_COUNTER_OUTPUT_HOME)|| (mode == IS_SERVO)){
				SetValFromAsync(i,Packet->use.data[i]);//asyncData[i].currentVal=Packet->use.data[i];
			}
		}
		//println_I("***Setting All Digital value: ");
	}else if (Packet->use.head.RPC==GetRPCValue("gacv")){
		int i;
		int val;
		for(i=0;i<GetNumberOfIOChannels();i++){
			val = get32bit(Packet, i*4);
			if(getBcsIoDataTable(i)->PIN.asyncDataCurrentVal!=val){
				println_W("Data on Pin ");p_int_W(i);print_W(" to val ");p_int_W(val);
				SetValFromAsync(i,val);//
			}
		}
	}else{
		println_W("***Async packet not UNKNOWN***");
		printPacket(Packet,WARN_PRINT);
	}
//	println_I("***Setting All value: [");
//	int i;
//	for(i=0;i<NUM_PINS;i++){
//		p_int_I(asyncData[i].currentVal);print_I(" ");
//	}
//	print_I("]");
	setPrintLevel(l);
}




boolean isAnalog(BowlerPacket * Packet){
	if(		(Packet->use.head.RPC==GCHV) &&
			(GetChannelMode(Packet->use.data[0])==IS_ANALOG_IN)
			){
		return true; 
	}
	return false; 
}

void dealWithAsyncPacket(BowlerPacket * Packet){
	if(Packet->use.head.RPC==_PWR){
		SetColor(1,0,0);
		return;
	}
	ProcessAsyncData(Packet);
}


//
//void RunAsync(void){
//	PushCoProcAsync();
//	runAsyncIO();
//}




