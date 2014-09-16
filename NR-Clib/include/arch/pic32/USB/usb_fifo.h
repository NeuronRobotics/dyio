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
void printBufferState(BYTE_FIFO_STORAGE  * s);

boolean GotUSBData(void);
BYTE_FIFO_STORAGE  * GetPICUSBFifo(void);
void SetPICUSBFifo(BYTE_FIFO_STORAGE  * s);

void usb_CDC_Serial_Init(char * DevStr,char * SerialStr,uint16_t vid,uint16_t pid);
uint16_t USBGetArray(BYTE* stream, uint16_t count);
int USBPutArray(BYTE* stream, int Len);
uint16_t GetNumUSBBytes(void);

void WriteUSBDeviceString(char * b);
void WriteUSBSerialNumber(char * b);
void SetUSB_VID_PID(uint16_t vid,uint16_t pid);

void usb_Buffer_Update(void);

/**
 * Checks to see if the USB port is opened by a host
 */
uint8_t isUSBActave();
/**
 * Forces open the USB for transmit
 */
void forceOpenUSB();

#endif /* USB_FIFO_H_ */
