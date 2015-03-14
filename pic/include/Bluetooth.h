/**
 * @fileBluetooth.h
 *
 *  Created on: May 19, 2012
 * @author Kevin Harrington
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define BluetoothResetTRIS()	setPicIOTristateOutput('D',1)
#define BluetoothCommandTRIS()	setPicIOTristateOutput('D',4)
#define BluetoothLinkTRIS()		setPicIOTristateOutput('D',6)

#define BluetoothReset(a)		setPicIOPin(a,'D',1)
#define BluetoothCommand(a)		setPicIOPin(a,'D',4)
#define BluetoothLink(a)		setPicIOPin(a,'D',6)

/**
 * Checks to see if the bluetooth module is present
 */
uint8_t hasBluetooth();
/**
 * Initialized the bluetooth module
 */
void initBluetooth();

#endif /* BLUETOOTH_H_ */
