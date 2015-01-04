/**
 * @filePPMReader.c
 *
 *  Created on: Feb 18, 2011
 * @author Kevin Harrington
 */

#include "UserApp.h"
uint8_t ppmData[]={128,128,128,128,128,128};
uint8_t ppmLastSent[]={255,255,255,255,255,255};
uint8_t ppmLink[]={255,255,255,255,255,255};
uint32_t ppmDataTmp[]={128,128,128,128,128,128};
uint32_t ppmStart[NUM_PPM_CHAN];
uint8_t ppmIndex = 0;
uint32_t bufferStart=0;
uint32_t buffTime = (TICKS_PER_SECOND/1000)*6;

void configPin23Int();

typedef enum{
	START=0,
	WAIT_FOR_PULSE,
	PULSE_STARTED
}ppmState ;
ppmState state;
boolean startedLinks=false;

boolean writeLinks=false;

void RunPPMCheck(void){
	if(GetChannelMode(23) != IS_PPM_IN){
		//setMode(23,IS_PPM_IN);
		return;
	}
	if(startedLinks==false){
		startedLinks=true;
		readPPMLink(ppmLink);
	}
	if(writeLinks==true){
		writeLinks=false;
		writePPMLink(ppmLink);
	}
	int i;
	boolean up = false; 
	for(i=0;i<NUM_PPM_CHAN;i++){
		float fTime =MyTickConvertToMilliseconds(((float)ppmDataTmp[i])+(((float)TickGetUpper())*((float) 4294967295ul )));
		if(fTime>.9 && fTime<2.2){
			float fVal = (fTime-.99)*255;
			if(fVal>254)
				fVal=254;
			if(fVal<0)
				fVal=0;
			uint8_t time =((BYTE) fVal);

			if((time>(ppmData[i]+3)) || (time<(ppmData[i]-3))){
				ppmData[i]=time;
				//setHeartBeatState( FALSE, 0);
				up=true; 
			}
		}
	}
	if(up){
		//push upstream
		pushPPMPacket();
		//print_I("\nUpdating ppm chan ");printStream(ppmData,NUM_PPM_CHAN);
		//print_I(" PPM cross link ");printStream(ppmLink,NUM_PPM_CHAN);
		for(i=0;i<NUM_PPM_CHAN;i++){
			if(ppmLink[i] != INVALID_PPM_LINK){
				if(ppmLastSent[i] != ppmData[i]){
					ppmLastSent[i] = ppmData[i];
					Print_Level l = getPrintLevel();
					setPrintLevelInfoPrint();
					//println_I("PPM setting output");
					//SetChannelValueCoProc(ppmLink[i],ppmData[i]);
					getBcsIoDataTable(ppmLink[i])->PIN.currentValue=ppmData[i];
					//SetValFromAsync(ppmLink[i],ppmData[i]);
					setPrintLevel(l);
				}
			}
		}
	}
}

void runPPMEvent(void){
	uint8_t pinState = CHAN3P1;
	uint32_t now = TickGet();
	if(pinState){
		mINT4SetEdgeMode(0);
	}else{
		mINT4SetEdgeMode(1);
	}

	switch(state){
	case START:
		if((bufferStart == 0) ||(pinState == 0 ))
			bufferStart = now;
		if((now>(bufferStart + buffTime))&&(pinState == 1)){
			state =  WAIT_FOR_PULSE;
		}
		// no break
	case WAIT_FOR_PULSE:
		if(pinState == 0 ){
			ppmStart[ppmIndex]=now;
			state = PULSE_STARTED;
		}
		break;
	case PULSE_STARTED:
		if(pinState == 1 ){
			ppmDataTmp[ppmIndex] = (now-ppmStart[ppmIndex]);
			ppmIndex++;
			if(ppmIndex == NUM_PPM_CHAN){
				ppmIndex = 0;
				state = START;
			}else{
				state = WAIT_FOR_PULSE;
			}
		}
		break;
	}
}

void clearPPM(uint8_t chan,uint8_t mode){
	if((chan == 23) && (mode==IS_PPM_IN)){
		CloseINT4();
		CHAN3P1_tris=INPUT;
	}
}

void startPPM(uint8_t chan){
	int i;
	if(chan == 23){
		configPin23Int();
		state = START;

		for(i=0;i<NUM_PPM_CHAN;i++){
			if(ppmLink[i]>= GetNumberOfIOChannels())
				ppmLink[i]=INVALID_PPM_LINK;
		}
		//println_I("Starting PPM reader");
	}
}

void GetPPMDataToPacket(BowlerPacket * Packet){
	//println_I("Getting PPM values");
	int i;
	LoadCorePacket(Packet);
	Packet->use.head.Method=BOWLER_POST;
	Packet->use.head.RPC=GetRPCValue("strm");
	Packet->use.data[0]=23;
	Packet->use.data[1]=NUM_PPM_CHAN*2;
	for(i=0;i<NUM_PPM_CHAN;i++){
		Packet->use.data[2+i]=ppmData[i];
	}
	for(i=0;i<NUM_PPM_CHAN;i++){
		Packet->use.data[2+i+NUM_PPM_CHAN]=ppmLink[i];
	}
	Packet->use.head.DataLegnth=4+1+1+(NUM_PPM_CHAN*2);
	Packet->use.head.MessageID=0;
	SetCRC(Packet);
}

void ConfigPPMFromArray(uint8_t * data){
	int i;
	for(i=0;i<NUM_PPM_CHAN;i++){
		ppmLink[i]=data[i];
		if(ppmLink[i]>= GetNumberOfIOChannels()){
			ppmLink[i]=INVALID_PPM_LINK;
		}else{
			unlockServos();
		}
	}
	writeLinks=true;

}

void ConfigPPM(BowlerPacket * Packet){
	int i;
	for(i=0;i<NUM_PPM_CHAN;i++){
		ppmLink[i]=Packet->use.data[i+1];
		if(ppmLink[i]>= GetNumberOfIOChannels()){
			ppmLink[i]=INVALID_PPM_LINK;
		}else{
			unlockServos();
		}
	}
	writeLinks=true;
	READY(Packet,66,0);
}

int GetPPMDataToArray(uint8_t * data){
	int i;
	for(i=0;i<NUM_PPM_CHAN;i++){
		data[i]=ppmData[i];
	}
	for(i=0;i<NUM_PPM_CHAN;i++){
		data[i+NUM_PPM_CHAN]=ppmLink[i];
	}
	return NUM_PPM_CHAN+NUM_PPM_CHAN;
}


