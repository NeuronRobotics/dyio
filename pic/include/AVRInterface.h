/*
 * AVRInterface.h
 *
 *  Created on: May 23, 2010
 *      Author: acamilo
 */

#ifndef AVRINTERFACE_H_
#define AVRINTERFACE_H_
void PowerCycleAVR();
void HoldAVRReset(void);
void ReleaseAVRReset(void);

boolean writeAVRTempFlashPageLowByte(uint8_t data, uint8_t address);
boolean writeAVRTempFlashPageHighByte(uint8_t data, uint8_t address);

#endif /* AVRINTERFACE_H_ */
