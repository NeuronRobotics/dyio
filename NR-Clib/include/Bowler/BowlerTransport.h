/*
 * BowlerTransport.h
 *
 *  Created on: May 27, 2010
 *      Author: hephaestus
 */

#ifndef BOWLERTRANSPORT_H_
#define BOWLERTRANSPORT_H_

#include "FIFO.h"
boolean GetBowlerPacket_arch(BowlerPacket * Packet);
boolean GetBowlerPacket(BowlerPacket * Packet,BYTE_FIFO_STORAGE * fifo);
boolean PutBowlerPacket(BowlerPacket * Packet);
void FixPacket(BowlerPacket * Packet);
boolean GetBowlerPacketDebug(BowlerPacket * Packet,BYTE_FIFO_STORAGE * fifo);

#endif /* BOWLERTRANSPORT_H_ */
