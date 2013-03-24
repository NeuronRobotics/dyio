/*
 * Abstract_bcs_io.c
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#include "Bowler/Bowler.h"


static int NumberOfIOChannels = 0;
static DATA_STRUCT * dataPtr = NULL;

BOOL (*setChanelValueHWPtr)(BYTE,BYTE*,INT32 *,float);
BOOL (*getChanelValueHWPtr)(BYTE,BYTE*,INT32 *);

void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal,
					BOOL (*setChanelValueHWPtrLocal)(BYTE,BYTE*,INT32 *,float),
					BOOL (*getChanelValueHWPtrLocal)(BYTE,BYTE*,INT32 *),
){
	if(	NumberOfIOChannels ==0||
		dataPtrLocal==NULL||
		setChanelValueHWPtrLocal==NULL||
		getChanelValueHWPtrLocal==NULL
	){
		//FAIL sanity check
		while(1);
	}

	NumberOfIOChannels = numPins;
	dataPtr = dataPtrLocal;
	setChanelValueHWPtr=setChanelValueHWPtrLocal;
	getChanelValueHWPtr=getChanelValueHWPtrLocal;
}


int getNumberOfIOChannels(){
	return NumberOfIOChannels;
}

BYTE GetChannelMode(BYTE chan){
	if(chan>0 && chan<getNumberOfIOChannels()){
		//FAIL sanity check
		while(1);
	}
	//Strip off the internally stored High Bit
	return getBcsIoDataTable()[chan].PIN.State & 0x7f;
}


DATA_STRUCT * getBcsIoDataTable(){
	if(dataPtr==NULL){
		//FAIL sanity check
		while(1);
	}
	return dataPtr;
}
