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

void InitilizeBcsIoSetmode(BOOL (*setChanelModeHWPtrLocal)(BYTE,BYTE));

NAMESPACE_LIST * get_bcsIoSetmodeNamespace();

/*
 * Set Channel Mode
 * Sets the given channel to the given mode
 * Returns true if successful
 */
BOOL SetChannelMode(BYTE chan,BYTE mode);
/*
 * Set Channel Mode
 * Sets the given channel to the given mode
 * Returns true if successful
 */
BOOL AbstractSetChannelMode(BowlerPacket * Packet);

/*
 * Set All channel modes
 * Iterates down the array of channel modes setting all of them
 * Returns true if all modes set OK
 */
BOOL SetAllChannelModes(BYTE * modeArray);

/*
 * Set All channel modes
 * Iterates down the array of channel modes setting all of them
 * Returns true if all modes set OK
 */
BOOL AbstractSetAllChannelMode(BowlerPacket * Packet);

#endif /* NAMESPACE_BCS_IO_SETMODE_H_ */
