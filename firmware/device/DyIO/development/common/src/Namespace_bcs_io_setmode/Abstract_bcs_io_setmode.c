/*
 * Abstract_bcs_io_setmode.c
 *
 *  Created on: Mar 24, 2013
 *      Author: hephaestus
 */
#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io_setmode.h"


BOOL (*setChanelModeHWPtr)(BYTE,BYTE);
/*
 * Initialize SetMode hardware interface functions
 */

void InitilizeBcsIoSetmode(BOOL (*setChanelModeHWPtrLocal)(BYTE,BYTE)){
	if(setChanelModeHWPtrLocal == NULL){
		while(1);
	}
	setChanelModeHWPtr = setChanelModeHWPtrLocal;
}

/*
 * Set Channel Mode
 * Sets the given channel to the given mode
 * Returns true if successful
 */
BOOL SetChannelMode(BYTE chan,BYTE mode){
	if(setChanelModeHWPtr == NULL)
		return FALSE;

	BOOL ok = setChanelModeHWPtr(chan,mode & 0x7);
	getBcsIoDataTable()[chan].PIN.currentChannelMode = mode;
	if(IsAsync(chan))
		startAdvancedAsyncDefault(chan);
	return ok;
}

/*
 * Set All channel modes
 * Iterates down the array of channel modes setting all of them
 * Returns true if all modes set OK
 */
BOOL SetAllChannelModes(BYTE * modeArray){
	int i=0;
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(!SetChannelMode(i,modeArray[i])){
			return FALSE;
		}
	}
	return TRUE;
}
/*
 * Set Channel Mode
 * Sets the given channel to the given mode
 * Returns true if successful
 */
BOOL AbstractSetChannelMode(BowlerPacket * Packet){
	BYTE pin =Packet->use.data[0];

	BYTE mode=Packet->use.data[1]& 0x7f;

	if(Packet->use.head.DataLegnth == 7){
		setAsync(pin,Packet->use.data[2]?TRUE:FALSE);
		//Grab the async flag
		mode = GetChannelMode(pin);
	}

	if(SetChannelMode(pin,mode)){
		READY(Packet,4,33);
		return TRUE;
	}else{
		println_E("Mode Invalid!");
		return FALSE;
	}

}
/*
 * Set All channel modes
 * Iterates down the array of channel modes setting all of them
 * Returns true if all modes set OK
 */
BOOL AbstractSetAllChannelMode(BowlerPacket * Packet){
	int i=0;
	for(i=0;i<GetNumberOfIOChannels();i++){
		SetChannelMode(i,Packet->use.data[i]);
	}
	return TRUE;
}