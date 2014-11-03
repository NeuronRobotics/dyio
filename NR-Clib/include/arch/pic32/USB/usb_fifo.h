/*
 * usb_fifo.h
 *
 *  Created on: Jun 3, 2010
 *      Author: hephaestus
 */

#ifndef USB_FIFO_H_
#define USB_FIFO_H_
#include "arch/pic32/Compiler.h"
#include "arch/pic32/GenericTypeDefs.h"
#include "arch/pic32/usb_config.h"
#include "arch/pic32/USB/usb_common.h"
#include "arch/pic32/USB/usb.h"
#include "arch/pic32/USB/usb_function_cdc.h"
//#include "USB/usb_function_hid.h"
#include "Bowler/Bowler.h"

#define USB_BUFFER_SIZE BOWLER_PacketSize

//BYTE_FIFO_STORAGE  * GetPICUSBFifo(void);
void USBDeviceTasksLocal(void);
BOOL GotUSBData(void);

void SetPICUSBFifo(BYTE_FIFO_STORAGE  * s);

void usb_CDC_Serial_Init(char * DevStr,char * SerialStr,UINT16 vid,UINT16 pid);
WORD USBGetArray(BYTE* stream, WORD count);
int USBPutArray(BYTE* stream, int Len);
WORD GetNumUSBBytes(void);

void WriteUSBDeviceString(char * b);
void WriteUSBSerialNumber(char * b);
void SetUSB_VID_PID(WORD vid,WORD pid);

void usb_Buffer_Update(void);

/**
 * Checks to see if the USB port is opened by a host
 */
BYTE isUSBActave();
/**
 * Forces open the USB for transmit
 */
void forceOpenUSB();

#endif /* USB_FIFO_H_ */
