/*
 * BowlerTransport.h
 *
 *  Created on: May 27, 2010
 *      Author: hephaestus
 */

#ifndef BOWLERTRANSPORT_H_
#define BOWLERTRANSPORT_H_

#include "FIFO.h"
BOOL GetBowlerPacket_arch(BowlerPacket * Packet);
BOOL GetBowlerPacket(BowlerPacket * Packet,BYTE_FIFO_STORAGE * fifo);
BOOL PutBowlerPacket(BowlerPacket * Packet);
void FixPacket(BowlerPacket * Packet);
BOOL GetBowlerPacketDebug(BowlerPacket * Packet,BYTE_FIFO_STORAGE * fifo);

#endif /* BOWLERTRANSPORT_H_ */
