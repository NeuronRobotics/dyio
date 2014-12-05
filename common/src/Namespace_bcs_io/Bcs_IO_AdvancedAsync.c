/**
 * @file Bcs_IO_AdvancedAsync.c
 *
 * Created on: Mar 18, 2013
 * @author hephaestus
 */


#include "Bowler/Bowler.h"
#include "Namespace/AsyncManager.h"
#include "Namespace/Namespace_bcs_io.h"

#define ADCINIT 0xFFFF
#define FASTIO

boolean isInit=false;

void initAdvancedAsync(){
	if(isInit == true) {
		//println_W("All ready initialized advanced async");
		return;
	}
	
	isInit=true; 
	int i;
	for (i=0;i<GetNumberOfIOChannels();i++){

			startAdvancedAsyncDefault(i);
	}
        println_W("Initializing advanced async");
}

void setAsync(uint8_t pin,boolean async){
	uint8_t mode = GetChannelMode(pin);
	getBcsIoDataTable(pin)->PIN.currentChannelMode = mode;
	setAsyncLocal(pin,async);
	startAdvancedAsyncDefault(pin);
}

void setAsyncLocal(uint8_t channel,boolean async){
	getBcsIoDataTable(channel)->PIN.asyncDataenabled=async;
}

boolean IsAsync(uint8_t channel){
	if (getBcsIoDataTable(channel)->PIN.asyncDataenabled){
		return true; 
	}
	uint8_t mode=GetChannelMode(channel);
	switch(mode){
	case IS_UART_RX:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_INPUT_INT:
	case IS_SERVO:
		return true; 
	default:
		return false; 
	}
}

void printAsyncType(uint8_t t){
	switch(t){
	case AUTOSAMP:
		print_I("AUTOSAMP");return;
	case NOTEQUAL:
		print_I("NOTEQUAL");return;
	case DEADBAND:
		print_I("DEADBAND");return;
	case THRESHHOLD:
		print_I("THRESHHOLD");return;
	default:
		print_I("UNKNOWN: "); p_int_I(t);return;
	}
}
void configAdvancedAsyncNotEqual(uint8_t pin,float time){
	getBcsIoDataTable(pin)->asyncDataTimer.MsTime=getMs();
	getBcsIoDataTable(pin)->asyncDataTimer.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = NOTEQUAL;
}
void configAdvancedAsyncDeadBand(uint8_t pin,float time,int32_t deadbandSize){
	getBcsIoDataTable(pin)->asyncDataTimer.MsTime=getMs();
	getBcsIoDataTable(pin)->asyncDataTimer.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = DEADBAND;
	getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval=deadbandSize;
}
void configAdvancedAsyncTreshhold(uint8_t pin,float time,int32_t threshholdValue, uint8_t edgeType){
	getBcsIoDataTable(pin)->asyncDataTimer.MsTime=getMs();
	getBcsIoDataTable(pin)->asyncDataTimer.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = THRESHHOLD;
	getBcsIoDataTable(pin)->PIN.asyncDatathreshholdval=threshholdValue;
	getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge=edgeType;
}
void configAdvancedAsyncAutoSample(uint8_t pin,float time){
	getBcsIoDataTable(pin)->asyncDataTimer.MsTime=getMs();
	getBcsIoDataTable(pin)->asyncDataTimer.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = AUTOSAMP;
}

boolean configAdvancedAsync(BowlerPacket * Packet){
	INT32_UNION val;
	INT32_UNION time;
	uint8_t pin = Packet->use.data[0];
	uint8_t type = Packet->use.data[1];
	time.byte.FB= Packet->use.data[2];
	time.byte.TB= Packet->use.data[3];
	time.byte.SB= Packet->use.data[4];
	time.byte.LB= Packet->use.data[5];
	switch(type){
	case AUTOSAMP:
		configAdvancedAsyncAutoSample(pin,time.Val);
		break;
	case NOTEQUAL:
		configAdvancedAsyncNotEqual(pin,time.Val);
		break;
	case DEADBAND:
		val.byte.FB= Packet->use.data[6];
		val.byte.TB= Packet->use.data[7];
		val.byte.SB= Packet->use.data[8];
		val.byte.LB= Packet->use.data[9];
		configAdvancedAsyncDeadBand(pin,time.Val,val.Val);
		break;
	case THRESHHOLD:
		val.byte.FB= Packet->use.data[6];
		val.byte.TB= Packet->use.data[7];
		val.byte.SB= Packet->use.data[8];
		val.byte.LB= Packet->use.data[9];
		configAdvancedAsyncTreshhold(pin,time.Val,val.Val,Packet->use.data[10]);
		break;
	default:
		ERR(Packet,45,0);
		break;
	}
	setAsync(Packet->use.data[0],true) ;
	READY(Packet,45,0);
	return true; 
}


void startAdvancedAsyncDefault(uint8_t pin){
	println_W("Starting advanced async on channel: ");p_int_W(pin);
	int mode =GetChannelMode(pin);
	if(isOutputMode(mode)==false){
		if(mode == IS_SERVO || mode == IS_PWM || mode == IS_DC_MOTOR_VEL ){
			setDataTableCurrentValue(pin,GetConfigurationDataTable(pin));
		}else{
			setDataTableCurrentValue(pin,1);
		}
	}
	getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=getDataTableCurrentValue(pin);
	getBcsIoDataTable(pin)->asyncDataTimer.MsTime=getMs();
	getBcsIoDataTable(pin)->asyncDataTimer.setPoint=10;
	getBcsIoDataTable(pin)->PIN.asyncDataType = NOTEQUAL;
        printMode(GetChannelMode(pin),INFO_PRINT);
	switch(GetChannelMode(pin)){
	case IS_DI:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_SERVO:
		getBcsIoDataTable(pin)->asyncDataTimer.setPoint=5;
		break;
	case IS_ANALOG_IN:
		setDataTableCurrentValue(pin,ADCINIT);
		getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=ADCINIT;
		getBcsIoDataTable(pin)->PIN.asyncDataType = DEADBAND;
		getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval=10;
		break;
	}

	RunEvery(getPinsScheduler( pin));
	//println_I("Async OK");
}

int GetValFromAsync(int pin){
	return getBcsIoDataTable(pin)->PIN.currentValue;
}

int GetDigitalValFromAsync(uint8_t pin){
	initAdvancedAsync();
	if(GetChannelMode(pin)==IS_DI || GetChannelMode(pin)==IS_COUNTER_INPUT_HOME || GetChannelMode(pin)==IS_COUNTER_OUTPUT_HOME ){
		return getBcsIoDataTable(pin)->PIN.currentValue;
	}
	return 1;
}


boolean pushAsyncReady( uint8_t pin){
	if(!IsAsync(pin)){
		//println_I("No asyinc on pin ");p_int_I(pin);print_I(" Mode 0x");prHEX8(GetChannelMode(pin),INFO_PRINT);
		return false; 
	}
//	println_I("Has async ");p_int_I(pin);print_I(" Mode 0x");prHEX8(GetChannelMode(pin),INFO_PRINT);
	initAdvancedAsync();
	int32_t last;
	int32_t aval;
	int32_t db;
	//int i=pin;
	EndCritical();
	RunEveryData * tRef=getPinsScheduler( pin);
//	println_I("Checking timer \nMsTime: ");p_fl_I(tRef->MsTime);
//	print_I(" \nSetpoint: ");p_fl_I(tRef->setPoint);
//	print_I(" \nCurrentTime: ");p_fl_I(getMs());
	float timeout = RunEvery(tRef);
//	print_I(" \nTimeout: ");p_fl_I(timeout);
	if(timeout !=0){
//		println_I("Time to do something");
		switch(getBcsIoDataTable(pin)->PIN.asyncDataType&0x0F){
		case AUTOSAMP:
//			println_I("Auto samp ");p_int_I(pin);
			getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = getBcsIoDataTable(pin)->PIN.currentValue;

			return true; 
		case NOTEQUAL:
			//
			if(getBcsIoDataTable(pin)->PIN.currentValue != getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal){
//				println_I("not equ ");p_int_I(pin);
//				printfDEBUG_uint8_t*('\t',INFO_PRINT);
//				p_int_I(getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal);
//				printfDEBUG_uint8_t*('\t',INFO_PRINT);
//				p_int_I(getBcsIoDataTable(pin)->PIN.currentValue);
				getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = getBcsIoDataTable(pin)->PIN.currentValue;
				return true; 
			}
			break;
		case DEADBAND:
			aval = getBcsIoDataTable(pin)->PIN.currentValue;
			last = getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal;
			db = getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval;
			if (	( 	( last >(aval+db)) ||
						( last <(aval-db)) ) &&
					(aval >=db)
					){
//				println_I("deadband");p_int_I(pin);
				getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=aval;
				return true; 
			}
			break;
		case THRESHHOLD:
//			println_I("treshhold");p_int_I(pin);
			aval = getBcsIoDataTable(pin)->PIN.currentValue;
			last = getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal;
			db = getBcsIoDataTable(pin)->PIN.asyncDatathreshholdval;
			getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = getBcsIoDataTable(pin)->PIN.currentValue;
			if(getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_RISING || getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_BOTH){
				if(last<= db && aval>db){

					return true; 
				}
			}
			if(getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_FALLING|| getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_BOTH){
				if(last> db && aval<=db){
					return true; 
				}
			}
			break;
		default:
			//print_I("\nNo type defined!! chan: ");p_int_I(pin);print_I(" mode: ");printMode(GetChannelMode(pin),INFO_PRINT);print_I(" type: ");printAsyncType(getBcsIoDataTable(pin)->PIN.asyncDataType);
			startAdvancedAsyncDefault(pin);
			break;
		}
	}else{
//		println_I("Nothing to do, returning");
	}
	return false; 
}

//void populateGACV(BowlerPacket * Packet){
//	INT32_UNION s;
//	LoadCorePacket(Packet);
//	Packet->use.head.Method=BOWLER_POST;
//	Packet->use.head.RPC=GetRPCValue("gacv");
//	Packet->use.head.DataLegnth=(GetNumberOfIOChannels()*4)+4+1;
//	Packet->use.head.MessageID=37;
//	int i;
//	for(i=0;i<GetNumberOfIOChannels();i++){
//		s.Val= getBcsIoDataTable(i)->PIN.currentValue;
//		Packet->use.data[(i*4)+0]=s.byte.FB;
//		Packet->use.data[(i*4)+1]=s.byte.TB;
//		Packet->use.data[(i*4)+2]=s.byte.SB;
//		Packet->use.data[(i*4)+3]=s.byte.LB;
//
//
//	}
//}


