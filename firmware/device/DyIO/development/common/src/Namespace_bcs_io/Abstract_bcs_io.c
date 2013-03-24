/*
 * Abstract_bcs_io.c
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#include "Bowler/Bowler.h"

static int NumberOfIOChannels = 0;
static DATA_STRUCT * dataPtr = NULL;

void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal
){
	if(	NumberOfIOChannels ==0||
		dataPtrLocal==NULL
	){
		//FAIL sanity check
		while(1);
	}

	NumberOfIOChannels = numPins;
	dataPtr = dataPtrLocal;

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
