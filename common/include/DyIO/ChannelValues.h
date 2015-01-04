/*
 * ChannelValues.h
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */

#ifndef CHANNELVALUES_H_
#define CHANNELVALUES_H_
#include "Bowler/Bowler.h"
/**
 * Get/Set the pin state to/from a packet
 * @return if the operatiion was a success
 */
boolean GetChannelValue(BowlerPacket * Packet);
boolean SetChannelValue(BowlerPacket * Packet);
boolean SetAllChannelValue(BowlerPacket * Packet);

/**
 * Retreives the value of a channel
 * Internaly checks the pin mode and calls the approprate method to access it
 * @return the value of that channel
 */
uint16_t GetChanVal(uint8_t pin);

/**
 * Sets the value of a channel(primitive only, no stream channels with this method)
 * @param pin the channel to be set
 * @param the value to set the mode to
 * @param time the time it takes for the transision (only valid with servo for now)
 * @return if it succeded
 */
boolean SetChanVal(uint8_t pin,int32_t bval, float time);

/**
 * Sets the value of a channel into non volitile storage
 */
boolean SaveValue(uint8_t pin,uint8_t val);

#endif /* CHANNELVALUES_H_ */
