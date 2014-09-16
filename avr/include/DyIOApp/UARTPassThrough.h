/*
 * UARTPassThrough.h
 *
 *  Created on: Apr 3, 2010
 *      Author: hephaestus
 */

#ifndef UARTPASSTHROUGH_H_
#define UARTPASSTHROUGH_H_

void InitUART(void);

boolean ConfigureUART(uint32_t baudrate);
void StopUartPassThrough(uint8_t pin);

void AddBytePassThrough(uint8_t b);
void UARTGetArrayPassThrough(uint8_t *packet,uint16_t size);
uint16_t Get_UART_Byte_CountPassThrough(void);

#endif /* UARTPASSTHROUGH_H_ */
