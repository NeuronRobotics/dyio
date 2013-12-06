/*
 * usb_fifo.c
 *
 *  Created on: Jun 3, 2010
 *      Author: hephaestus
 */

/**
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "arch/pic32/USB/usb_fifo.h"
#include "Bowler/Bowler.h"

#define USBNotOk	(USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)

#define TxPrivateSize 64
static BYTE RxTmpBuffer[BOWLER_PacketSize*2];
static BYTE privateRX[BOWLER_PacketSize*2];
static BYTE TxBuffer[TxPrivateSize+1 ];
static UINT16 gotData = 0;
static BOOL bufferSet=FALSE;

static WORD     txSize;


static BYTE_FIFO_STORAGE store;
static BYTE_FIFO_STORAGE * my_store;

static BOOL usbActive = TRUE;

BOOL GotUSBData(void){
	return gotData>0;
}

BYTE_FIFO_STORAGE  * GetPICUSBFifo(void){
	return my_store;
}

void SetPICUSBFifo(BYTE_FIFO_STORAGE  * s){
	if(bufferSet==TRUE)
		return;
	bufferSet=TRUE;
	my_store=s;
}

void usb_CDC_Serial_Init(char * DevStr,char * SerialStr,UINT16 vid,UINT16 pid){

	//unsigned char i;
	DelayMs(100);
	SetUSB_VID_PID(vid,pid);
	WriteUSBSerialNumber(SerialStr);
	WriteUSBDeviceString(DevStr);
	#if defined(USE_USB_BUS_SENSE_IO)
		tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
	#endif
	#if defined(USE_SELF_POWER_SENSE_IO)
		tris_self_power = INPUT_PIN;	// See HardwareProfile.h
	#endif
	USBDeviceInit();
	InitByteFifo(&store,privateRX,sizeof(privateRX));
	if(bufferSet==FALSE)
		my_store=&store;
	#if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif
    INTEnableSystemMultiVectoredInt();
    usb_Buffer_Update();
}

WORD USBGetArray(BYTE* stream, WORD num){
	if(USBNotOk){
		return  0;
	}
	usb_Buffer_Update();
	gotData-=num;
	BYTE n = FifoGetByteStream(my_store,stream,num);
	return n;
}
//static BYTE tmp [64];
extern BYTE cdc_trf_state;
extern USB_HANDLE CDCDataInHandle;

#define isUSBTxBlocked() ((cdc_trf_state != CDC_TX_READY)  || (USBHandleBusy(CDCDataInHandle)!=0))

void waitForTxToBeFree(){
	RunEveryData timeout={getMs(),200};
	while(isUSBTxBlocked()){
		if(RunEvery(&timeout)>0){
			println_E("#*#*USB timeout before transmit");
			usbActive=FALSE;
                        break;
		}
		if(USBNotOk){
			println_E("#*#*USB Not ok");
                        usbActive=FALSE;
                        break;
		}
		CDCTxService();
	}

}

void flush(){

	float start = getMs();

	waitForTxToBeFree();

	float end = getMs()-start;
	//println_I("USB Buffer ready, took:");p_fl_I(end);
	start = getMs();


	if(txSize>0){
		putUSBUSART((char *)TxBuffer, txSize);
		//DelayMs(2);
		txSize=0;
	}else{
		//println_I("Zero length packet to send, ignoring");
	}

	waitForTxToBeFree();

	end = getMs()-start;
	//println_I("USB Flushed OK, took:");p_fl_I(end);
}

BYTE isUSBActave(){
    return usbActive;
}

void forceOpenUSB(){
    usbActive=TRUE;
}

int USBPutArray(BYTE* stream, int num){
	if(isUSBActave()==FALSE){
		//println_I("USB inactive, bailing out");
		return 0;
	}
	//UINT16 i;

	usb_Buffer_Update();
	if(USBNotOk){
		usbActive=FALSE;
		return  0;
	}else{
		int packetLen = num;
		int packetIndex = 0;
		int i;
		//if(num>(TxPrivateSize)) {
		if(num>255) {
			//println_I("Packet too large for USB buffer");
			while(packetLen>TxPrivateSize) {
				for(i=0;i<TxPrivateSize;i++) {
					TxBuffer[i]=stream[packetIndex++];
					packetLen--;
				}
				//println_I("Sending chunk ");printStream_I(TxBuffer,i);
				txSize=i;
				flush();
			}
			for(i=0;i<packetLen;i++) {
				TxBuffer[i]=stream[packetIndex++];
			}
			//println_I("Sending chunk ");printStream_I(TxBuffer,i);
			txSize=i;
			flush();
		}else {
			//println_I("Packet small enough for USB buffer");
			for (i=0;i<num;i++){
				TxBuffer[i]=stream[i];
			}
			//println_I("Sending all ");printStream_I(TxBuffer,num);
			txSize=i;
			flush();
		}
	}
	return TRUE;
}


WORD GetNumUSBBytes(void){
	usb_Buffer_Update();
	return FifoGetByteCount(my_store);
}


void usb_Buffer_Update(void){
	if(USBNotOk){
		usbActive=FALSE;
		return ;
	}
	WORD i;
	WORD gSize=getsUSBUSART((char *)RxTmpBuffer, USB_BUFFER_SIZE);
	BYTE err;
	if (gSize>0){
		for(i=0;i<gSize;i++){
			do{
				FifoAddByte(my_store,RxTmpBuffer[i], & err);
			}while(err != FIFO_OK );
			gotData++;
			usbActive = TRUE;
		}
	}

}

