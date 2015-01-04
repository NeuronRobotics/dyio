/**
 * @fileBluetooth.h
 *
 *  Created on: May 19, 2012
 * @author Kevin Harrington
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define BluetoothResetTRIS		_TRISD1
#define BluetoothCommandTRIS	_TRISD4
#define BluetoothLinkTRIS		_TRISD6

#define BluetoothReset			_RD1
#define BluetoothCommand		_RD4
#define BluetoothLink			_RD6

/**
 * Checks to see if the bluetooth module is present
 */
uint8_t hasBluetooth();
/**
 * Initialized the bluetooth module
 */
void initBluetooth();

#endif /* BLUETOOTH_H_ */
