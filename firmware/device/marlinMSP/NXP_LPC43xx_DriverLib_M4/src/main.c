
/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "chip_lpc43xx.h"
#endif

#include "gpio_18xx_43xx.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	// initialized GPIO hardware
	Chip_GPIO_Init();

	// Set GPIO pins 1-3 of port 3 for write output
	Chip_GPIO_SetDir(3,1,true);
	Chip_GPIO_SetDir(3,2,true);
	Chip_GPIO_SetDir(3,3,true);
	Chip_GPIO_WriteDirBit(3,1,true);
	Chip_GPIO_WriteDirBit(3,2,true);
	Chip_GPIO_WriteDirBit(3,3,true);



	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		Chip_GPIO_WritePortBit(3,1,true);
		Chip_GPIO_WritePortBit(3,2,true);


		i++ ;
	}
	return 0 ;
}
