/*
 * BLdefines.h
 *
 *  Created on: May 30, 2010
 *      Author: hephaestus
 */

#ifndef BLDEFINES_H_
#define BLDEFINES_H_

#define StartAppVectVirtual				0x9D00A000

#define StartAppVectPhysical			0x1D00A000
#define EndAppVectPhysical				0x1D01F000


	// acamilo:
	// 		change fuses to f7
	// 		SUT changed to int64_t to increase oscilator stabalization time.
	// 		Oscilator drive method changed to FullSwing from Low Power.
	// 		SEE DS section 8.4 (p. 34)
#define AVR_LOW			0xf7
#define AVR_HIGH		0xd1
#define AVR_EXT			0xff

#endif /* BLDEFINES_H_ */
