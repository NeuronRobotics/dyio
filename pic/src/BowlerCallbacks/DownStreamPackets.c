/**
 * @file DownStreamPackets.c
 *
 * Created on: Dec 4, 2010
 * @author hephaestus
 */

#include "UserApp.h"
static BowlerPacket packetTemp;
uint8_t isAscii(char * str);

boolean bankA=true , bankB=true;
uint8_t batteryCode0=0,batteryCode1=0;

static Downstream_Data down[NUM_PINS];

void LoadDefaultValues(){
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("save");
	SendPacketToCoProc(& packetTemp);
	uint8_t i;
	for (i=0;i<GetNumberOfIOChannels();i++){
		//getBcsIoDataTable(i)->PIN.currentConfiguration=packetTemp.use.data[i];
	}
}

//void SetCoProcLED(boolean a, boolean b, int batt){
//	LoadCorePacket(& packetTemp);
//	POWER(& packetTemp);
//	packetTemp.use.data[0]=a;
//	packetTemp.use.data[1]=b;
//	packetTemp.use.data[2]=0;
//	packetTemp.use.data[3]=batt;
//	SendPacketToCoProc(& packetTemp);
//}

void setCoProcBrownOutMode(boolean b){
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_CRIT;
	packetTemp.use.head.RPC=GetRPCValue("_pwr");
	packetTemp.use.head.DataLegnth=4+1;
	packetTemp.use.data[0]=b?0:1;
	SendPacketToCoProc(& packetTemp);
}

void DownstreamPowerChange(void){

	LoadCorePacket(& packetTemp);
	POWER(& packetTemp);

	packetTemp.use.data[2]=GetRawVoltageCode(0);
	packetTemp.use.data[3]=GetRawVoltageCode(1);

	if(		packetTemp.use.data[0]==bankA &&
			packetTemp.use.data[1]==bankB &&
			packetTemp.use.data[2]==batteryCode0 &&
			packetTemp.use.data[3]==batteryCode1)
			return;
	bankA=packetTemp.use.data[0];
	bankB=packetTemp.use.data[1];
	batteryCode0=packetTemp.use.data[2];
	batteryCode1=packetTemp.use.data[3];

	SendPacketToCoProc(& packetTemp);

}
void LoadGACM(BowlerPacket * pack){
	LoadCorePacket(pack);
	pack->use.head.Method=BOWLER_GET;
	pack->use.head.RPC=GetRPCValue("gacm");
	pack->use.head.DataLegnth=4;
	SetCRC(& packetTemp);
}
void GetAllModes(BowlerPacket * pack){
	println_I("GetAllModes");
	int total=0;
	do{
		total++;
		if (total>5){
			println_I("Failed returning");
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
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("_rev");
	packetTemp.use.head.DataLegnth=4;
	SendPacketToCoProc(& packetTemp);
	if((packetTemp.use.data[0]==MAJOR_REV) && (packetTemp.use.data[1]==MINOR_REV) && (packetTemp.use.data[2]==FIRMWARE_VERSION) ){
		SetColor(0,0,1);
	}else{
		SetColor(1,0,0);
		println_I("Rev. Check Failed! AVR:");
		p_int_I(packetTemp.use.data[0]);
		print_I(".");
		p_int_I(packetTemp.use.data[1]);
		print_I(".");
		p_int_I(packetTemp.use.data[2]);
		print_I(" PIC:");
		p_int_I(MAJOR_REV);
		print_I(".");
		p_int_I(MINOR_REV);
		print_I(".");
		p_int_I(FIRMWARE_VERSION);

	}
}

uint8_t SetCoProcMode(uint8_t pin,uint8_t mode){
	if(getBcsIoDataTable(pin)->PIN.currentChannelMode == mode)
		return true; 
	getBcsIoDataTable(pin)->PIN.currentChannelMode=mode;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("schm");
	packetTemp.use.data[0]=pin;
	packetTemp.use.data[1]=mode;
	packetTemp.use.data[2]=(IsAsync(pin))?1:0;
	packetTemp.use.head.DataLegnth=7;
	SendPacketToCoProc(& packetTemp);
	down[pin].previousChannelMode=mode;
	return false; 
}

uint8_t SetAllCoProcMode(){
	int i=0;
	boolean send = false; 
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(getBcsIoDataTable(i)->PIN.currentChannelMode != down[i].previousChannelMode ){
			 send=true; 
		}
	}
	if(send){

		LoadCorePacket(& packetTemp);
		packetTemp.use.head.Method=BOWLER_POST;
		packetTemp.use.head.RPC=GetRPCValue("sacm");
		packetTemp.use.head.DataLegnth = 4;
		for(i=0;i<GetNumberOfIOChannels();i++){
			packetTemp.use.data[i]=getBcsIoDataTable(i)->PIN.currentChannelMode ;
			down[i].previousChannelMode =getBcsIoDataTable(i)->PIN.currentChannelMode ;
			packetTemp.use.head.DataLegnth++;
		}
                println_I("Sending mode sync packet");printPacket(&packetTemp,INFO_PRINT);
		SendPacketToCoProc(& packetTemp);
	}
	return true; 
}
uint8_t SetAllCoProcValues(){
	int i=0;
	boolean send = false; 
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(getBcsIoDataTable(i)->PIN.currentValue != down[i].previousValue ){
			 send=true; 
		}
	}
	int32_t tmp;
	if(send){
		LoadCorePacket(& packetTemp);
		packetTemp.use.head.Method=BOWLER_POST;
		packetTemp.use.head.RPC=GetRPCValue("sacv");
		packetTemp.use.head.DataLegnth = 4;
		for(i=0;i<GetNumberOfIOChannels();i++){
			tmp = getBcsIoDataTable(i)->PIN.currentValue ;
			down[i].previousValue =getBcsIoDataTable(i)->PIN.currentValue ;
			set32bit(& packetTemp,tmp,i*4);
			packetTemp.use.head.DataLegnth +=4;
		}
		SendPacketToCoProc(& packetTemp);
	}
	return true; 
}

void SetChannelValueCoProc(uint8_t PIN,uint8_t state){
	uint8_t retry = 0;
	do{
		if(retry>0){
			println_E("#*#*SetChannelValueCoProc did not return RDY pin: ");p_int_E(PIN);print_E(" mode: ");printMode(GetChannelMode(PIN),ERROR_PRINT);
			printPacket(&packetTemp,ERROR_PRINT);
			return;
		}
		LoadCorePacket(& packetTemp);
		packetTemp.use.head.Method=BOWLER_POST;
		packetTemp.use.head.RPC=GetRPCValue("schv");
		packetTemp.use.data[0]=PIN;
		packetTemp.use.data[1]=state;
		packetTemp.use.data[2]=0;
		packetTemp.use.data[3]=0;
		packetTemp.use.head.DataLegnth=8;
		SendPacketToCoProc(& packetTemp);
		retry++;
		buttonCheck(13);
	}while(packetTemp.use.head.RPC != _RDY);

}

uint8_t GetChannelValueCoProc(uint8_t PIN){
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("gchv");
	packetTemp.use.data[0]=PIN;
	packetTemp.use.head.DataLegnth=5;
	SendPacketToCoProc(& packetTemp);
	if (packetTemp.use.head.RPC==_ERR)
			return 1;
	SetValFromAsync(PIN, packetTemp.use.data[1]);
	return packetTemp.use.data[1];
}

uint16_t GetADC(uint8_t PIN){
	WORD_VAL v;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("gchv");
	packetTemp.use.data[0]=PIN;
	packetTemp.use.head.DataLegnth=5;
	SendPacketToCoProc(& packetTemp);
	if (packetTemp.use.head.RPC==_ERR){
		println_I("Failed to get adc");
		return 1;
	}
	v.byte.HB=packetTemp.use.data[1];
	v.byte.LB=packetTemp.use.data[2];
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

void GetEEPRomData(uint8_t start,uint8_t stop,uint8_t * data){
	println_I("Getting eeprom page: ");p_int_I(start);print_I(" to ");p_int_I(stop);
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
		LoadCorePacket(& packetTemp);
		for (i=0;i<(stop-start);i++){
			//Writes over the old packet to avoid mis-reads
			packetTemp.use.data[i] = data[i];
		}
		packetTemp.use.head.Method=BOWLER_GET;
		packetTemp.use.head.RPC=GetRPCValue("eepd");
		packetTemp.use.data[0]=start+DATASTART;
		packetTemp.use.data[1]=stop+DATASTART;
		packetTemp.use.head.DataLegnth=6;
		SendPacketToCoProc(& packetTemp);
		buttonCheck(12);
	}while(packetTemp.use.head.RPC != GetRPCValue("eepd"));

	for (i=0;i<(stop-start);i++){
		data[i]=packetTemp.use.data[i];
	}
}

void SetEEPRomData(uint8_t start,uint8_t stop,uint8_t * data){
	println_I("Setting eeprom page: ");p_int_I(start);print_I(" to ");p_int_I(stop);
	//WORD_VAL raw;
	uint8_t i=0;
	if (start>=stop)
		return;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("eepd");
	packetTemp.use.data[0]=start+DATASTART;
	packetTemp.use.data[1]=stop+DATASTART;
	for (i=0;i<(stop-start);i++){
		packetTemp.use.data[2+i]=data[i];
	}
	packetTemp.use.head.DataLegnth=6+stop-start;
	println_I("Sent data to coproc's eeprom");
	SendPacketToCoProc(& packetTemp);
}

boolean GetName(char * name){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("eepd");
	packetTemp.use.data[0]=NAMESTART;
	packetTemp.use.data[1]=LOCKSTART;
	packetTemp.use.head.DataLegnth=6;
	SendPacketToCoProc(& packetTemp);
	while (packetTemp.use.data[i]!='\0'){
		name[i]=packetTemp.use.data[i];
		i++;
		buttonCheck(11);
	}
	name[i]='\0';
	return isAscii(name);
}

boolean GetLockCode(char * code){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("eepd");
	packetTemp.use.data[0]=LOCKSTART;
	packetTemp.use.data[1]=DATASTART;
	packetTemp.use.head.DataLegnth=6;
	SendPacketToCoProc(& packetTemp);
	while (packetTemp.use.data[i+2]!='\0'){
		code[i]=packetTemp.use.data[2+i];
		i++;
		buttonCheck(10);
	}
	code[i]='\0';
	return isAscii(code);
}

void SetName(char * name){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("eepd");
	packetTemp.use.data[0]=NAMESTART;
	packetTemp.use.data[1]=LOCKSTART;
	while (name[i]!='\0'){
		packetTemp.use.data[2+i]=name[i];
		i++;
		buttonCheck(9);
	}
	packetTemp.use.data[2+i]='\0';
	packetTemp.use.head.DataLegnth=6+i+1;
	SendPacketToCoProc(& packetTemp);
}

void SetLockCode(char * code){
	//WORD_VAL raw;
	uint8_t i=0;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("eepd");
	packetTemp.use.data[0]=LOCKSTART;
	packetTemp.use.data[1]=DATASTART;
	while (code[i]!='\0'){
		packetTemp.use.data[2+i]=code[i];
		i++;
		buttonCheck(8);
	}
	packetTemp.use.data[2+i]='\0';
	packetTemp.use.head.DataLegnth=6+5;
	SendPacketToCoProc(& packetTemp);
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
	GetAllModes(& packetTemp);
	for (i=0;i<NUM_PINS;i++){
            if(packetTemp.use.data[i] == NO_CHANGE){
                getBcsIoDataTable(i)->PIN.currentChannelMode=IS_DI;
                down[i].previousChannelMode = NO_CHANGE;// force a sync later
                println_E("FAULT: the mode was set to NO_CHANGE");
            }else{
                getBcsIoDataTable(i)->PIN.currentChannelMode=packetTemp.use.data[i];
                down[i].previousChannelMode=packetTemp.use.data[i];
            }
	}
}

