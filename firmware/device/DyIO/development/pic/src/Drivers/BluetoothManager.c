
/**
 * This file is for managment of the onboard bluetooth module
 */
#include "UserApp.h"

BYTE hasBluetooth(){
	//TODO check for bluetooth module
	return TRUE;
}

void initBluetooth(){
	_TRISD1=0; //output mode on reset line
	_TRISD4=0; //output mode on CMD line
	_RD1=1; // Pull BT module out of reset
	mPORTDOpenDrainClose(BIT_2 | BIT_3); // make sure the com port is driven 3.3
	//_RD4=1; // enter command mode. this doesn't work cause i re-used the pin for RD4. Sorry kevin

}
