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
        //println_W("Initializing advanced async");
}

void setAsync(uint8_t pin,boolean async){
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
//	switch(t){
//	case AUTOSAMP:
//		print_I("AUTOSAMP");return;
//	case NOTEQUAL:
//		print_I("NOTEQUAL");return;
//	case DEADBAND:
//		print_I("DEADBAND");return;
//	case THRESHHOLD:
//		print_I("THRESHHOLD");return;
//	default:
//		print_I("UNKNOWN: "); p_int_I(t);return;
//	}
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
	// this sets default async mode and clears and setting of async mode
	setAsyncLocal(Packet->use.data[0],true) ;

	//printPacket(Packet,ERROR_PRINT);
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
	getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=0xffffffff;// invalid previous, forces a value update
	READY(Packet,45,0);
	return true; 
}


void startAdvancedAsyncDefault(uint8_t pin){
	//println_W("Starting advanced async on channel: ");p_int_W(pin);
	int mode =GetChannelMode(pin);
	if(isOutputMode(mode)==false){
		if(mode == IS_SERVO || mode == IS_PWM || mode == IS_DC_MOTOR_VEL ){
			setDataTableCurrentValue(pin,GetConfigurationDataTable(pin));
		}else{
			setDataTableCurrentValue(pin,1);
		}
	}
	getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=0xffffffff;;
	getBcsIoDataTable(pin)->asyncDataTimer.MsTime=getMs();
	getBcsIoDataTable(pin)->asyncDataTimer.setPoint=10;
	getBcsIoDataTable(pin)->PIN.asyncDataType = NOTEQUAL;

	RunEvery(getPinsScheduler( pin));
}

int GetValFromAsync(int pin){
	if(GetChannelMode(pin)== IS_SERVO){
		return GetServoPos(pin);
	}else{
		return getDataTableCurrentValue(pin);
	}
}

int GetDigitalValFromAsync(uint8_t pin){
	initAdvancedAsync();
	if(GetChannelMode(pin)==IS_DI || GetChannelMode(pin)==IS_COUNTER_INPUT_HOME || GetChannelMode(pin)==IS_COUNTER_OUTPUT_HOME ){
		return getDataTableCurrentValue(pin);
	}
	if(GetChannelMode(pin)== IS_SERVO){
		return GetServoPos(pin);
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
	//EndCritical();

//	println_I("Checking timer \nMsTime: ");p_fl_I(tRef->MsTime);
//	print_I(" \nSetpoint: ");p_fl_I(tRef->setPoint);
//	print_I(" \nCurrentTime: ");p_fl_I(getMs());
	float timeout = RunEvery(getPinsScheduler( pin));
//	print_I(" \nTimeout: ");p_fl_I(timeout);
	if(GetChannelMode(pin)== IS_SERVO){
		aval = GetServoPos(pin);
	}else{
		aval = getDataTableCurrentValue(pin);
	}

	if(timeout !=0){
//		println_I("Time to do something");
		switch(getBcsIoDataTable(pin)->PIN.asyncDataType){
		case AUTOSAMP:
//			println_I("Auto samp ");p_int_I(pin);
			getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = aval;

			return true; 
		case NOTEQUAL:
			//
			if(aval != getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal){
//				println_I("not equ ");p_int_I(pin);
//				printfDEBUG_uint8_t*('\t',INFO_PRINT);
//				p_int_I(getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal);
//				printfDEBUG_uint8_t*('\t',INFO_PRINT);
//				p_int_I(getBcsIoDataTable(pin)->PIN.currentValue);
				getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = aval;
				return true; 
			}
			break;
		case DEADBAND:
			last = getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal;
			db = getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval;

			if(!bound(last,aval,db,db)){
//				println_I("deadband");p_int_I(pin);
				getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=aval;
				return true; 
			}
			break;
		case THRESHHOLD:
//			println_I("treshhold");p_int_I(pin);
			last = getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal;
			db = getBcsIoDataTable(pin)->PIN.asyncDatathreshholdval;

			if(getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_RISING || getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_BOTH){
				if(last<= db && aval>db){
					getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = aval;
					return true; 
				}
			}
			if(getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_FALLING|| getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_BOTH){
				if(last> db && aval<=db){
					getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = aval;
					return true; 
				}
			}
			break;
		default:
			println_E("\nNo type defined!! chan: ");p_int_E(pin);
			print_E(" mode: ");printMode(GetChannelMode(pin),ERROR_PRINT);
			print_E(" type: ");printAsyncType(getBcsIoDataTable(pin)->PIN.asyncDataType);
			startAdvancedAsyncDefault(pin);
			break;
		}
	}else{
//		println_I("Nothing to do, returning");
	}
	return false; 
}


