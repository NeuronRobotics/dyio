/*
 * CoProcCom.h
 *
 *  Created on: Nov 21, 2009
 *      Author: hephaestus
 */

#ifndef COPROCCOM_H_
#define COPROCCOM_H_
void addCoProcByte(uint8_t b);
boolean isProcessing();
void startUartCoProc();
void initCoProcCom(void);
void SendPacketToCoProc(BowlerPacket * Packet);

void GetPacketUARTCoProc(uint8_t *packet,uint16_t size);
uint16_t Get_UART_Byte_CountCoProc(void);
boolean SendPacketUARTCoProc(uint8_t * packet,uint16_t size);



#endif /* COPROCCOM_H_ */
