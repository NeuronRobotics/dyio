
/**
 * This file is for managment of the onboard bluetooth module
 */
#include "UserApp.h"

BYTE hasBluetooth(){
	//TODO check for bluetooth module
	return TRUE;
}

#define BluetoothResetTRIS		_TRISD1
#define BluetoothCommandTRIS	_TRISD4
#define BluetoothLinkTRIS		_TRISD6

#define BluetoothReset			_RD1
#define BluetoothCommand		_RD4
#define BluetoothLink			_RD6



void initBluetooth(){
	BluetoothResetTRIS=0; //output mode on reset line
	BluetoothCommandTRIS=0; //output mode on CMD line
	BluetoothReset=1; // Pull BT module out of reset
	mPORTDOpenDrainClose(BIT_2 | BIT_3); // make sure the com port is driven 3.3
	//_RD4=1; // enter command mode. this doesn't work cause i re-used the pin for RD4. Sorry kevin

}
