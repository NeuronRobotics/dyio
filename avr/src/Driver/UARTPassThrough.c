/*
 * UARTPassThrough.c
 *
 *  Created on: Apr 3, 2010
 *      Author: hephaestus
 */

#include "UserApp_avr.h"

#if defined(__AVR_ATmega324P__)
	#define UART_PASS_BUFF_SIZE 5
#else
	#define UART_PASS_BUFF_SIZE 60
#endif


uint8_t privateRXUART[UART_PASS_BUFF_SIZE];
BYTE_FIFO_STORAGE UARTPassThroughStore;

boolean validBaud(uint32_t baud);

static boolean UartInit = false;



void InitUART(void){
	if(UartInit == true){
		return;
	}

	if (!(	pinHasFunction(16,IS_UART_TX)||
			pinHasFunction(17,IS_UART_RX)
		)){
		println_W("Pins Failed UART Test");
		return;
	}
	println_W("Uart Initialization: ");
	if(getPrintLevel() == NO_PRINT){
		uint32_t baudrate = EEReadBaud();
		if (validBaud(baudrate) == false) {
			baudrate = 19200;
			validBaud(baudrate);
		}
	}
	SetPinTris(16,OUTPUT);
	SetPinTris(17,INPUT);
	SetDIO(17,ON);
	InitByteFifo(&UARTPassThroughStore,privateRXUART,UART_PASS_BUFF_SIZE);

	/* set the framing to 8N1 */
	UCSR1C = ((1<< UCSZ10)|(1<< UCSZ11));
	/* rx interrupts enabled, rx and tx enabled, 8-bit data */
	UCSR1B =( _BV(RXCIE1) | _BV(RXEN1) | _BV(TXEN1));
	UCSR1A = 0x00;
	UartInit=true;

}
void StopUartPassThrough(uint8_t pin){
	if(UartInit == false){
		return;
	}
	println_E("Uart STOP: ");
	if (!(	pinHasFunction(pin,IS_UART_RX)||
			pinHasFunction(pin,IS_UART_TX)
		)){
		return;
	}
	UCSR1Bbits._RXCIE1=0;
	if(getPrintLevel() == NO_PRINT)
		UCSR1B=0;
	//InitByteFifo(&UARTPassThroughStore,privateRXUART,sizeof(privateRXUART));
	switch(GetChannelMode(pin)){
		case IS_UART_TX:
		case IS_UART_RX:
			configPinMode(16,IS_DI,INPUT,ON);
			configPinMode(17,IS_DI,INPUT,ON);
			UartInit=false;
	}
}

boolean ConfigureUART(uint32_t baudrate){
	if(getPrintLevel() != NO_PRINT)
		return true;
	return validBaud(baudrate);
}

boolean validBaud(uint32_t baud){
	switch(baud){
	case   2400:
		UBRR1=479;
		break;
	case   4800:
		UBRR1=239;
		break;
	case   9600:
		UBRR1=119;
		break;
	case  14400:
		UBRR1=79;
		break;
	case  19200:
		UBRR1=59;
		break;
	case  28800:
		UBRR1=39;
		break;
	case  38400:
		UBRR1=29;
		break;
	case  57600:
		UBRR1=19;
		break;
	case  76800:
		UBRR1=14;
		break;
	case 115200:
		UBRR1=9;
		break;
	case 230400:
		UBRR1=4;
		break;
	default:
		return false; 
	}
	EEWriteBaud(baud);
	return true; 
}

/**
 * Private helpers
 */
ISR(USART1_RX_vect){
	uint8_t read;
	//UCSR1Bbits._RXCIE1=0;
	//while ((UCSR0A & 0x80) == 0 );
	read = UDR1;
	//AddBytePassThrough(read);
	if(UartInit){
		uint8_t err;
		FifoAddByte(&UARTPassThroughStore,read,&err);
		//WriteAVRUART1(read);
		//p_int_W(Get_UART_Byte_CountPassThrough());
	}
	//UCSR1Bbits._RXCIE1=1;
}
ISR(USART1_TX_vect){

}
ISR(USART1_UDRE_vect){

}
void UARTGetArrayPassThrough(uint8_t *packet,uint16_t size){
	println_W("Reading: ");p_int_W(size);
	if(UartInit)
		FifoGetByteStream(&UARTPassThroughStore,packet,size);
}

uint16_t Get_UART_Byte_CountPassThrough(void){
	if(UartInit)
		return FifoGetByteCount(&UARTPassThroughStore);
	else{
		return 0;
	}
}

void UARTPassThroughWrite(uint8_t numValues,uint8_t * data){
	println_W("Writing: ");p_int_W(numValues);print_W(" ");
	int i;
	//uint8_t err;
	for(i=0;i<numValues;i++){
		WriteAVRUART1(data[i]);
		//FifoAddByte(&UARTPassThroughStore,data[i],&err);
	}
	print_W(" done");
}

