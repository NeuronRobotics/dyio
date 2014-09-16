/*
 * ChannelMode.h
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */

#ifndef CHANNELMODE_H_
#define CHANNELMODE_H_
/**
 * Initialize the internal data structures from the eeprom
 */
void InitPinModes(void);
void InitPinStates(void);

/**
 * Helper macro to return the mode with the async flag stripped off
 */
uint8_t GetChannelMode(uint8_t chan);

/**
 * Sets the modes from an incoming packet
 */
boolean SetChannelModeFromPacket(BowlerPacket * Packet);
boolean SetAllChannelModeFromPacket(BowlerPacket * Packet);



/**
 * Checks to see if the channel is set to async mode
 * @return if it is async
 */
boolean IsAsync(uint8_t channel);

/**
 * This Function is used to alter the mode of the pin (See DYIO_def.h for modes)
 * Setting the higest bit (|=0x80) will enable the mode as async
 *
 * @param pin The pin refers to the dyio channel to be altered
 * @param mode the mode to set the pin to
 * @return If the mode change was successfull
 */
boolean setMode(uint8_t pin,uint8_t mode);


/**
 * Private method
 */
void configPinMode(uint8_t pin,uint8_t mode,uint8_t tris,uint8_t io);
#endif /* CHANNELMODE_H_ */
