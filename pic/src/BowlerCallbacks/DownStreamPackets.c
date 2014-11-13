/**
 * @file DownStreamPackets.c
 *
 * Created on: Dec 4, 2010
 * @author hephaestus
 */

#include "UserApp.h"
BowlerPacket downstreamPacketTemp;
  uint8_t isAscii(char * str);

  boolean bankA=true , bankB=true;
  uint8_t batteryCode0=0,batteryCode1=0;

Downstream_Data down[NUM_PINS];


void forceValueDownstream(int8_t pin){
      down[pin].changeValue =true;
}
void forceModeDownstream(int8_t pin){
      down[pin].changeMode =true;
}

void LoadDefaultValues(){
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_GET;
	downstreamPacketTemp.use.head.RPC=GetRPCValue("save");
	SendPacketToCoProc(& downstreamPacketTemp);
	uint8_t i;
	for (i=0;i<GetNumberOfIOChannels();i++){
		//getBcsIoDataTable(i)->PIN.currentConfiguration=downstreamPacketTemp.use.data[i];
            down[i].changeMode =false;
            down[i].changeValue =false;
	}
}

//void SetCoProcLED(boolean a, boolean b, int batt){
//	LoadCorePacket(& downstreamPacketTemp);
//	POWER(& downstreamPacketTemp);
//	downstreamPacketTemp.use.data[0]=a;
//	downstreamPacketTemp.use.data[1]=b;
//	downstreamPacketTemp.use.data[2]=0;
//	downstreamPacketTemp.use.data[3]=batt;
//	SendPacketToCoProc(& downstreamPacketTemp);
//}

void setCoProcBrownOutMode(boolean b){
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_CRIT;
	downstreamPacketTemp.use.head.RPC=GetRPCValue("_pwr");
	downstreamPacketTemp.use.head.DataLegnth=4+1;
	downstreamPacketTemp.use.data[0]=b?0:1;
	SendPacketToCoProc(& downstreamPacketTemp);
}

void DownstreamPowerChange(void){

	LoadCorePacket(& downstreamPacketTemp);
	POWER(& downstreamPacketTemp);

	downstreamPacketTemp.use.data[2]=GetRawVoltageCode(0);
	downstreamPacketTemp.use.data[3]=GetRawVoltageCode(1);

	if(		downstreamPacketTemp.use.data[0]==bankA &&
			downstreamPacketTemp.use.data[1]==bankB &&
			downstreamPacketTemp.use.data[2]==batteryCode0 &&
			downstreamPacketTemp.use.data[3]==batteryCode1)
			return;
	bankA=downstreamPacketTemp.use.data[0];
	bankB=downstreamPacketTemp.use.data[1];
	batteryCode0=downstreamPacketTemp.use.data[2];
	batteryCode1=downstreamPacketTemp.use.data[3];

	SendPacketToCoProc(& downstreamPacketTemp);

}
void LoadGACM(BowlerPacket * pack){
	LoadCorePacket(pack);
	pack->use.head.Method=BOWLER_GET;
	pack->use.head.RPC=GetRPCValue("gacm");
	pack->use.head.DataLegnth=4;
	SetCRC(& downstreamPacketTemp);
}
void GetAllModes(BowlerPacket * pack){
//	println_I("GetAllModes");
	int total=0;
	do{
		total++;
		if (total>5){
//			println_I("Failed returning");
			return;
		}
		LoadGACM(pack);
		SendPacketToCoProc(pack);
		buttonCheck(14);
	}while(pack->use.head.RPC != GetRPCValue("gacm"));
	//print_I("..done");
	//SetColor(0,0,1);
}

void CheckRev(void){
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_GET;
	downstreamPacketTemp.use.head.RPC=GetRPCValue("_rev");
	downstreamPacketTemp.use.head.DataLegnth=4;
	SendPacketToCoProc(& downstreamPacketTemp);
	if((downstreamPacketTemp.use.data[0]==MAJOR_REV) && (downstreamPacketTemp.use.data[1]==MINOR_REV) && (downstreamPacketTemp.use.data[2]==FIRMWARE_VERSION) ){
		SetColor(0,0,1);
	}else{
//		SetColor(1,0,0);
//		println_I("Rev. Check Failed! AVR:");
//		p_int_I(downstreamPacketTemp.use.data[0]);
//		print_I(".");
//		p_int_I(downstreamPacketTemp.use.data[1]);
//		print_I(".");
//		p_int_I(downstreamPacketTemp.use.data[2]);
//		print_I(" PIC:");
//		p_int_I(MAJOR_REV);
//		print_I(".");
//		p_int_I(MINOR_REV);
//		print_I(".");
//		p_int_I(FIRMWARE_VERSION);

	}
}

uint8_t SetCoProcMode(uint8_t pin,uint8_t mode){
	if(getBcsIoDataTable(pin)->PIN.currentChannelMode == mode)
		return true; 
	getBcsIoDataTable(pin)->PIN.currentChannelMode=mode;
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_POST;
	downstreamPacketTemp.use.head.RPC=GetRPCValue("schm");
	downstreamPacketTemp.use.data[0]=pin;
	downstreamPacketTemp.use.data[1]=mode;
	downstreamPacketTemp.use.data[2]=(IsAsync(pin))?1:0;
	downstreamPacketTemp.use.head.DataLegnth=7;
	SendPacketToCoProc(& downstreamPacketTemp);
	down[pin].changeMode=true;
	return false; 
}

uint8_t SetAllCoProcMode(){
	int i=0;
	boolean send = false; 
	for(i=0;i<GetNumberOfIOChannels();i++){
		if( down[i].changeMode ==true){
			 send=true; 
		}
	}
	if(send){

		LoadCorePacket(& downstreamPacketTemp);
		downstreamPacketTemp.use.head.Method=BOWLER_POST;
		downstreamPacketTemp.use.head.RPC=GetRPCValue("sacm");
                downstreamPacketTemp.use.data[0] = GetNumberOfIOChannels();
		for(i=0;i<GetNumberOfIOChannels();i++){
			downstreamPacketTemp.use.data[i+1]=getBcsIoDataTable(i)->PIN.currentChannelMode ;
			down[i].changeMode=false ;
		}
                downstreamPacketTemp.use.head.DataLegnth = 4+1+GetNumberOfIOChannels();
//                println_I("Sending mode sync packet");printPacket(&packetTemp,INFO_PRINT);
		SendPacketToCoProc(& downstreamPacketTemp);
                for (i=0;i<NUM_PINS;i++){
                    if(downstreamPacketTemp.use.data[i+1] == NO_CHANGE){
                        getBcsIoDataTable(i)->PIN.currentChannelMode=IS_DI;
                        down[i].changeMode = true;// force a sync of the no valid mode
                        //println_E("FAULT: the mode was set to NO_CHANGE");
                    }else{
                        getBcsIoDataTable(i)->PIN.currentChannelMode=downstreamPacketTemp.use.data[i+1];
                        down[i].changeMode = false;
                    }
                }

	}
	return true; 
}
//int32_t valueLocal;
uint8_t SetAllCoProcValues(){
	int i=0;
	boolean send = true;
//	for(i=0;i<GetNumberOfIOChannels();i++){
//		if( down[i].changeValue == true){
//                    //println_W("Pin Value Changed ");p_int_W(i);print_W(" to ");p_int_W(getBcsIoDataTable(i)->PIN.currentValue);
//			 send=true;
//                         SetChannelValueCoProc(i,getBcsIoDataTable(i)->PIN.currentValue);
//                         down[i].changeValue =false ;
//		}
//	}
//	for(i=0;i<GetNumberOfIOChannels();i++){
//		if(GetChannelMode(i)==IS_ANALOG_IN){
//			GetADC(i);
//		}
//	}
	int32_t tmp;
	if(send){
		LoadCorePacket(& downstreamPacketTemp);
		downstreamPacketTemp.use.head.Method=BOWLER_POST;
		downstreamPacketTemp.use.head.RPC=GetRPCValue("sacv");
                set32bit(& downstreamPacketTemp,123,0);// setting the translation time
                downstreamPacketTemp.use.data[4] = GetNumberOfIOChannels();
		for(i=0;i<GetNumberOfIOChannels();i++){
			tmp = getBcsIoDataTable(i)->PIN.currentValue ;
			down[i].changeValue =false ;
			set32bit(& downstreamPacketTemp,tmp,(i*4)+5);
		}

                downstreamPacketTemp.use.head.DataLegnth = 4+4+1+(4*GetNumberOfIOChannels());
//                clearPrint();
//                println_W("Syncing channel values ");printPacket(&downstreamPacketTemp,WARN_PRINT);
		SendPacketToCoProc(& downstreamPacketTemp);
//		printPacket(&downstreamPacketTemp,ERROR_PRINT);
	}


	for(i=0;i<GetNumberOfIOChannels();i++){
            if(SetValFromAsync(i,get32bit(& downstreamPacketTemp, (i*4)+1))){
            	getBcsIoDataTable(i)->PIN.asyncDataenabled = true;
            }
	}

//        valueLocal = GetValFromAsync(23);
        //SetChanelValueHW(22, 1, &valueLocal, 0);
//        Print_Level l = getPrintLevel();
//        setPrintLevelInfoPrint();
//        clearPrint();
//        printValues();
//        //printModes();
//        setPrintLevel(l);
	return true;
}

void SetChannelValueCoProc(uint8_t PIN,uint8_t state){
	uint8_t retry = 0;
	do{
		if(retry>0){

			//println_E("#*#*SetChannelValueCoProc did not return RDY pin: ");p_int_E(PIN);print_E(" mode: ");printMode(GetChannelMode(PIN),ERROR_PRINT);
			printPacket(&downstreamPacketTemp,ERROR_PRINT);
			return;
		}
		LoadCorePacket(& downstreamPacketTemp);
		downstreamPacketTemp.use.head.Method=BOWLER_POST;
		downstreamPacketTemp.use.head.RPC=GetRPCValue("schv");
		downstreamPacketTemp.use.data[0]=PIN;
		downstreamPacketTemp.use.data[1]=state;
		downstreamPacketTemp.use.data[2]=0;
		downstreamPacketTemp.use.data[3]=0;
		downstreamPacketTemp.use.head.DataLegnth=8;
		SendPacketToCoProc(& downstreamPacketTemp);
		retry++;
		buttonCheck(13);
	}while(downstreamPacketTemp.use.head.RPC != _RDY);

}

uint8_t GetChannelValueCoProc(uint8_t PIN){
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_GET;
	downstreamPacketTemp.use.head.RPC=GetRPCValue("gchv");
	downstreamPacketTemp.use.data[0]=PIN;
	downstreamPacketTemp.use.head.DataLegnth=5;
	SendPacketToCoProc(& downstreamPacketTemp);
	if (downstreamPacketTemp.use.head.RPC==_ERR)
			return 1;
	SetValFromAsync(PIN, downstreamPacketTemp.use.data[1]);
	return downstreamPacketTemp.use.data[1];
}

uint16_t GetADC(uint8_t PIN){
	WORD_VAL v;

	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_GET;
	downstreamPacketTemp.use.head.RPC=GetRPCValue("gchv");
	downstreamPacketTemp.use.data[0]=PIN;
	downstreamPacketTemp.use.head.DataLegnth=5;
	SendPacketToCoProc(& downstreamPacketTemp);
	if (downstreamPacketTemp.use.head.RPC==_ERR){
		println_I("Failed to get adc");
		return 1;
	}
	v.byte.HB=downstreamPacketTemp.use.data[1];
	v.byte.LB=downstreamPacketTemp.use.data[2];

	SetValFromAsync(PIN, v.Val);
	return v.Val;
}

boolean GetSerialStream(BowlerPacket * packet){
	//WORD_VAL v;
	LoadCorePacket(packet);
	packet->use.head.Method=BOWLER_GET;
	packet->use.head.RPC=GetRPCValue("gchv");
	packet->use.head.MessageID=55;
	packet->use.data[0]=17;
	packet->use.head.DataLegnth=5;
	SendPacketToCoProc(packet);
	packet->use.data[0]=17;
	if (packet->use.head.RPC ==_ERR){
		return false; 
	}
	if (packet->use.head.DataLegnth>5){
		return true; 
	}
	return false; 
}

char * eepd = "eepd";
void GetEEPRomData(uint8_t start,uint8_t stop,uint8_t * data){
//	println_I("Getting eeprom page: ");p_int_I(start);print_I(" to ");p_int_I(stop);
	//WORD_VAL raw;
	uint8_t i=0;
	if (start>stop){
		println_I("###ERROR, index for eeprom read bad!");
		return;
	}
	int total=0;
	do{
		total++;
		if (total>5)
			return;
		LoadCorePacket(& downstreamPacketTemp);
		for (i=0;i<(stop-start);i++){
			//Writes over the old packet to avoid mis-reads
			downstreamPacketTemp.use.data[i] = data[i];
		}
		downstreamPacketTemp.use.head.Method=BOWLER_GET;
		downstreamPacketTemp.use.head.RPC=GetRPCValue(eepd);
		downstreamPacketTemp.use.data[0]=start+DATASTART;
		downstreamPacketTemp.use.data[1]=stop+DATASTART;
		downstreamPacketTemp.use.head.DataLegnth=6;
		SendPacketToCoProc(& downstreamPacketTemp);
		buttonCheck(12);
	}while(downstreamPacketTemp.use.head.RPC != GetRPCValue(eepd));

	for (i=0;i<(stop-start);i++){
		data[i]=downstreamPacketTemp.use.data[i];
	}
}

void SetEEPRomData(uint8_t start,uint8_t stop,uint8_t * data){
//	println_I("Setting eeprom page: ");p_int_I(start);print_I(" to ");p_int_I(stop);
	//WORD_VAL raw;
	uint8_t i=0;
	if (start>=stop)
		return;
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_POST;
	downstreamPacketTemp.use.head.RPC=GetRPCValue(eepd);
	downstreamPacketTemp.use.data[0]=start+DATASTART;
	downstreamPacketTemp.use.data[1]=stop+DATASTART;
	for (i=0;i<(stop-start);i++){
		downstreamPacketTemp.use.data[2+i]=data[i];
	}

	downstreamPacketTemp.use.head.DataLegnth=6+stop-start;
	println_I("Sent data to coproc's eeprom");
	SendPacketToCoProc(& downstreamPacketTemp);
}

boolean GetName(char * name){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_GET;
	downstreamPacketTemp.use.head.RPC=GetRPCValue(eepd);
	downstreamPacketTemp.use.data[0]=NAMESTART;
	downstreamPacketTemp.use.data[1]=LOCKSTART;
	downstreamPacketTemp.use.head.DataLegnth=6;
	SendPacketToCoProc(& downstreamPacketTemp);
	while (downstreamPacketTemp.use.data[i]!='\0'){
		name[i]=downstreamPacketTemp.use.data[i];
		i++;
		buttonCheck(11);
                if(i==NAMESIZE)
                    break;
	}
	name[i]='\0';
	return isAscii(name);
}

boolean GetLockCode(char * code){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_GET;
	downstreamPacketTemp.use.head.RPC=GetRPCValue(eepd);
	downstreamPacketTemp.use.data[0]=LOCKSTART;
	downstreamPacketTemp.use.data[1]=DATASTART;
	downstreamPacketTemp.use.head.DataLegnth=6;
	SendPacketToCoProc(& downstreamPacketTemp);
	while (downstreamPacketTemp.use.data[i+2]!='\0'){
		code[i]=downstreamPacketTemp.use.data[2+i];
		i++;
		buttonCheck(10);
                if(i==LOCKSIZE)
                    break;
	}
	code[i]='\0';
	return isAscii(code);
}

void SetName(char * name){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_POST;
	downstreamPacketTemp.use.head.RPC=GetRPCValue(eepd);
	downstreamPacketTemp.use.data[0]=NAMESTART;
	downstreamPacketTemp.use.data[1]=LOCKSTART;
	while (name[i]!='\0'){
		downstreamPacketTemp.use.data[2+i]=name[i];
		i++;
		buttonCheck(9);
                if(i==NAMESIZE)
                    break;
	}
	downstreamPacketTemp.use.data[2+i]='\0';
	downstreamPacketTemp.use.head.DataLegnth=6+i+1;
	SendPacketToCoProc(& downstreamPacketTemp);
}

void SetLockCode(char * code){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& downstreamPacketTemp);
	downstreamPacketTemp.use.head.Method=BOWLER_POST;
	downstreamPacketTemp.use.head.RPC=GetRPCValue(eepd);
	downstreamPacketTemp.use.data[0]=LOCKSTART;
	downstreamPacketTemp.use.data[1]=DATASTART;
	while (code[i]!='\0'){
		downstreamPacketTemp.use.data[2+i]=code[i];
		i++;
		buttonCheck(8);
                if(i==LOCKSIZE)
                    break;
	}
	downstreamPacketTemp.use.data[2+i]='\0';
	downstreamPacketTemp.use.head.DataLegnth=6+5;
	SendPacketToCoProc(& downstreamPacketTemp);
}

uint8_t isAscii(char * str){
	if (str[0] < 48){
		return false; 
	}
	if(str[0] > 122){
		return false; 
	}
	return true; 
}

void SyncModes(void){

	uint8_t i;
	GetAllModes(& downstreamPacketTemp);
	for (i=0;i<NUM_PINS;i++){
            if(downstreamPacketTemp.use.data[i+1] == NO_CHANGE){
                getBcsIoDataTable(i)->PIN.currentChannelMode=IS_DI;
                down[i].changeMode = true;// force a sync of the no valid mode
                //println_E("FAULT: the mode was set to NO_CHANGE");
            }else{
                getBcsIoDataTable(i)->PIN.currentChannelMode=downstreamPacketTemp.use.data[i+1];
                down[i].changeMode = false;
            }
	}
}

