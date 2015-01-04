/*
 * Namespace_bcs_io_setmode.h
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#ifndef NAMESPACE_BCS_IO_SETMODE_H_
#define NAMESPACE_BCS_IO_SETMODE_H_
#include "Namespace/Namespace_bcs_io.h"
//bcs.io.setmode
#define SCHM				0x6D686373// Set channel mode
#define SACM				0x6D636173// Set all channel modes

/*
 * Initialize SetMode hardware interface functions
 */

void InitilizeBcsIoSetmode(boolean (*setChanelModeHWPtrLocal)(uint8_t,uint8_t));

NAMESPACE_LIST * get_bcsIoSetmodeNamespace();

/*
 * Set Channel Mode
 * Sets the given channel to the given mode
 * Returns true if successful
 */
boolean SetChannelMode(uint8_t chan,uint8_t mode);
/*
 * Set Channel Mode
 * Sets the given channel to the given mode
 * Returns true if successful
 */
boolean AbstractSetChannelMode(BowlerPacket * Packet);

/*
 * Set All channel modes
 * Iterates down the array of channel modes setting all of them
 * Returns true if all modes set OK
 */
boolean SetAllChannelModes(uint8_t * modeArray);

/*
 * Set All channel modes
 * Iterates down the array of channel modes setting all of them
 * Returns true if all modes set OK
 */
boolean AbstractSetAllChannelMode(BowlerPacket * Packet);

#endif /* NAMESPACE_BCS_IO_SETMODE_H_ */
