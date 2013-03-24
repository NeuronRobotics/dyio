/**
 * @file DownStreamPackets.c
 *
 * Created on: Dec 4, 2010
 * @author hephaestus
 */

#include "UserApp.h"
extern DATA_STRUCT * DATA __attribute__ ((section (".scs_global_var")));
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
static BowlerPacket packetTemp;
BYTE isAscii(char * str);

void LoadCorePacket(BowlerPacket * Packet){
	//SetColor(0,1,0);
	BYTE i;
	Packet->use.head.ProtocolRevision=BOWLER_VERSION;
	for (i=0;i<6;i++){
		Packet->use.head.MAC.v[i]=0;
	}
	Packet->use.head.MessageID=1;
	Packet->use.head.ResponseFlag=1;
	Packet->use.head.Method=BOWLER_STATUS;
	Packet->use.head.RPC=GetRPCValue("****");
	Packet->use.head.DataLegnth=4;
}

void LoadDefaultValues(){
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("save");
	SendPacketToCoProc(& packetTemp);
	BYTE i;
	for (i=0;i<NUM_PINS;i++){
		DATA[i].PIN.ServoPos=packetTemp.use.data[i];
	}
}

void SetCoProcLED(BOOL a, BOOL b, int batt){
	LoadCorePacket(& packetTemp);
	POWER(& packetTemp);
	packetTemp.use.data[0]=a;
	packetTemp.use.data[1]=b;
	packetTemp.use.data[2]=0;
	packetTemp.use.data[3]=batt;
	SendPacketToCoProc(& packetTemp);
}

void setCoProcBrownOutMode(BOOL b){
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
	packetTemp.use.head.MessageID=37;
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
		p_sl_I(packetTemp.use.data[0]);
		print_I(".");
		p_sl_I(packetTemp.use.data[1]);
		print_I(".");
		p_sl_I(packetTemp.use.data[2]);
		print_I(" PIC:");
		p_sl_I(MAJOR_REV);
		print_I(".");
		p_sl_I(MINOR_REV);
		print_I(".");
		p_sl_I(FIRMWARE_VERSION);

	}
}

BYTE SetCoProcMode(BYTE PIN,BYTE mode){
	if(DATA[PIN].PIN.State == mode)
		return TRUE;
	DATA[PIN].PIN.State=mode;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("schm");
	packetTemp.use.data[0]=PIN;
	packetTemp.use.data[1]=mode & 0x7f;
	packetTemp.use.data[2]=(mode>0x80)?1:0;
	packetTemp.use.head.DataLegnth=7;
	SendPacketToCoProc(& packetTemp);
	return FALSE;
}

BYTE SetAllCoProcMode(BYTE * mode){
	int i=0;
	BOOL send = FALSE;
	for(i=0;i<getNumberOfIOChannels();i++){
		if(DATA[i].PIN.State != mode[i]){
			 send=TRUE;
		}
	}
	if(send){
		LoadCorePacket(& packetTemp);
		packetTemp.use.head.Method=BOWLER_POST;
		packetTemp.use.head.RPC=GetRPCValue("sacm");
		packetTemp.use.head.DataLegnth = 4;
		for(i=0;i<getNumberOfIOChannels();i++){
			packetTemp.use.data[i]=mode[i];
			packetTemp.use.head.DataLegnth++;
		}
		SendPacketToCoProc(& packetTemp);
	}
	return TRUE;
}

void SetChannelValueCoProc(BYTE PIN,BYTE state){
	BYTE retry = 0;
	do{
		if(retry>0){
			println_E("#*#*SetChannelValueCoProc did not return RDY pin: ");p_sl_E(PIN);print_E(" mode: ");printMode(GetChannelMode(PIN),ERROR_PRINT);
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

BYTE GetChannelValueCoProc(BYTE PIN){
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

WORD GetADC(BYTE PIN){
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

BOOL GetSerialStream(BowlerPacket * packet){
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
		return FALSE;
	}
	if (packet->use.head.DataLegnth>5){
		return TRUE;
	}
	return FALSE;
}

void GetEEPRomData(BYTE start,BYTE stop,BYTE * data){
	println_I("Getting eeprom page: ");p_ul_I(start);print_I(" to ");p_ul_I(stop);
	//WORD_VAL raw;
	BYTE i=0;
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

void SetEEPRomData(BYTE start,BYTE stop,BYTE * data){
	println_I("Setting eeprom page: ");p_ul_I(start);print_I(" to ");p_ul_I(stop);
	//WORD_VAL raw;
	BYTE i=0;
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

BOOL GetName(char * name){
	//WORD_VAL raw;
	BYTE i=0;
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

BOOL GetLockCode(char * code){
	//WORD_VAL raw;
	BYTE i=0;
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
	BYTE i=0;
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
	BYTE i=0;
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

BYTE isAscii(char * str){
	if (str[0] < 48){
		return FALSE;
	}
	if(str[0] > 122){
		return FALSE;
	}
	return TRUE;
}

void SyncModes(void){

	BYTE i;
	GetAllModes(& packetTemp);
	for (i=0;i<24;i++){
		DATA[i].PIN.State=packetTemp.use.data[i] & 0x7f;
		setAsyncLocal(i,(packetTemp.use.data[i]>0x80)?TRUE:FALSE);
	}
}

