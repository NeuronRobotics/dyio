/*
 * Push.c
 *
 *  Created on: Sep 24, 2010
 *      Author: hephaestus
 */

#include "UserApp_avr.h"
#define send(a) WriteAVRUART0(a);//_delay_us(UARTDELAY);
void sendHeader(uint8_t legnth,char * rpc){
	uint8_t i;
	send(BOWLER_VERSION);
	for(i=0;i<6;i++){
		send(0);//broadcast mac
	}
	send(BOWLER_ASYN);
	send((0x80|0));//Set the response flag and set an async ID
	send(legnth);
	uint8_t crc =(uint8_t ) (BOWLER_VERSION+BOWLER_ASYN+(0x80|0)+legnth);
	send(crc);
	for(i=0;i<4;i++){
		send(rpc[i]);//rpc bytes
	}
}

boolean avrAsyncCallbackPtr(BowlerPacket *Packet){
	FixPacket(Packet);
	//println_I("<<Async\n\r");printPacket(Packet,INFO_PRINT);
	int i;
	for(i=0;i<Packet->use.head.DataLegnth+BowlerHeaderSize;i++){
		send(Packet->stream[i]);
	}
	return true; 
}

void PushSerial(void){
	uint16_t num = Get_UART_Byte_CountPassThrough();
	//FlagBusy_IO=1;
	//_delay_us(800);
	sendHeader(4+1+num,"gchv");
	send(17);
	uint16_t i;
	uint8_t b;
	for(i=0;i<num;i++){
		UARTGetArrayPassThrough(&b,1);
		send(b);
	}
	//FlagBusy_IO=0;
	//_delay_us(800);
}

//void PushAllAdcVal(){
//#if defined(WPIRBE)
//	return;
//#endif
//	//println_I("Pushing analog");
//	UINT16_UNION an;
//	//FlagBusy_IO=1;
//	//_delay_us(800);
//	sendHeader(4+16,"aasn");
//	int i=0;
//	for(i=8;i<16;i++){
//		an.Val=GetValFromAsync(i);
//		send(an.byte.SB);
//		send(an.byte.LB);
//	}
//	//FlagBusy_IO=0;
//	//_delay_us(800);
//}
//
//void PushADCval(uint8_t pin,uint16_t val){
//#if defined(WPIRBE)
//	return;
//#endif
//	UINT16_UNION an;
//	an.Val=val;
//	//FlagBusy_IO=1;
//	//_delay_us(800);
//	sendHeader(4+3,"gchv");
//	send(pin);
//	send(an.byte.SB);
//	send(an.byte.LB);
//	//FlagBusy_IO=0;
//	//_delay_us(800);
//}
//void PushAllDiVal(){
//#if defined(WPIRBE)
//	return;
//#endif
//	println_I("Pushing digital");
//	//FlagBusy_IO=1;
//	//_delay_us(800);
//	sendHeader(4+24,"dasn");
//	int i=0;
//	for(i=0;i<24;i++){
//		send(GetValFromAsync(i));
//	}
//	//FlagBusy_IO=0;
//	//_delay_us(800);
//
//}
//
//void PushDIval(uint8_t pin,uint8_t val){
//#if defined(WPIRBE)
//	return;
//#endif
//	//FlagBusy_IO=1;
//	//_delay_us(800);
//	sendHeader(4+2,"gchv");
//	send(pin);
//	send(val);
//	//FlagBusy_IO=0;
//	//_delay_us(800);
//}
