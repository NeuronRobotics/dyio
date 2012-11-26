/**********************************************************************
* $Id$		lpc43xx_gpio.c		2011-06-02
*//**
* @file		lpc43xx_gpio.c
* @brief	Contains all functions support for GPIO firmware library
* 			on lpc43xx
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup GPIO
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc43xx_gpio.h"
#include "lpc_types.h"

/* If this source file built with example, the lpc43xx FW library configuration
 * file in each example directory ("lpc43xx_libcfg.h") must be included,
 * otherwise the default FW library configuration file must be included instead
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc43xx_libcfg.h"
#else
#include "lpc43xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */


#ifdef _GPIO

/* Private Functions ---------------------------------------------------------- */

/* End of Private Functions --------------------------------------------------- */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup GPIO_Public_Functions
 * @{
 */


/* GPIO ------------------------------------------------------------------------------ */

/*********************************************************************//**
 * @brief		Set Direction for GPIO port.
 * @param[in]	portNum	Port Number value, should be in range from 0 to 4
 * @param[in]	bitValue	Value that contains all bits to set direction,
 * 				in range from 0 to 0xFFFFFFFF.
 * 				example: value 0x5 to set direction for bit 0 and bit 1.
 * @param[in]	dir	Direction value, should be:
 * 					- 0: Input.
 * 					- 1: Output.
 * @return		None
 *
 * Note:
 * All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
{
	if (dir)
	{
		LPC_GPIO_PORT->DIR[portNum] |= bitValue;
	} else
		{
		LPC_GPIO_PORT->DIR[portNum] &= ~bitValue;
	}
}


/*********************************************************************//**
 * @brief		Set Value for bits that have output direction on GPIO port.
 * @param[in]	portNum	Port number value, should be in range from 0 to 4
 * @param[in]	bitValue Value that contains all bits on GPIO to set, should
 * 				be in range from 0 to 0xFFFFFFFF.
 * 				example: value 0x5 to set bit 0 and bit 1.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void GPIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_PORT->SET[portNum] = bitValue;
}


/*********************************************************************//**
 * @brief		Clear Value for bits that have output direction on GPIO port.
 * @param[in]	portNum	Port number value, should be in range from 0 to 4
 * @param[in]	bitValue Value that contains all bits on GPIO to clear, should
 * 				be in range from 0 to 0xFFFFFFFF.
 * 				example: value 0x5 to clear bit 0 and bit 1.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void GPIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_PORT->CLR[portNum] = bitValue;
}


/*********************************************************************//**
 * @brief		Read Current state on port pin that have input direction of GPIO
 * @param[in]	portNum	Port number to read value, in range from 0 to 4
 * @return		Current value of GPIO port.
 *
 * Note: Return value contain state of each port pin (bit) on that GPIO regardless
 * its direction is input or output.
 **********************************************************************/
uint32_t GPIO_ReadValue(uint8_t portNum)
{
	return LPC_GPIO_PORT->PIN[portNum];
}


#ifdef GPIO_PIN_INT
/*********************************************************************//**
 * @brief		Enable GPIO interrupt
 * @param[in]	pinInt		Pin interrupt number, should be: 0 to 7
 * @param[in]	portNum		Port number to read value, should be: 0 to 7
 * @param[in]	bitValue	Value that contains all bits on GPIO to enable,
 * 				should be in range from 0 to 0xFFFFFFFF.
 * @param[in]	intMode		interrupt mode, should be:
 * 					- 0: Rising edge interrupt mode
 * 					- 1: Falling edge interrupt mode
 * 					- 2: Active-High interrupt mode
 * 					- 3: Active-Low interrupt mode
 * @return		None
 **********************************************************************/
void GPIO_IntCmd(uint8_t pinInt, uint8_t portNum, uint32_t bitValue, uint8_t intMode)
{
	switch(pinInt)
	{
		case 0:
			LPC_SCU->PINTSEL0 = ((portNum<<5)|(bitValue));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= 0x0;
					LPC_GPIO_PIN_INT->IENR |= 0x1;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= 0x0;
					LPC_GPIO_PIN_INT->IENF |= 0x1;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 0x1;
					LPC_GPIO_PIN_INT->IENR |= 0x1;
					LPC_GPIO_PIN_INT->SIENF |= 0x1;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 0x1;
					LPC_GPIO_PIN_INT->IENR |= 0x1;
					LPC_GPIO_PIN_INT->CIENF |= 0x1;
					break;
				default:
					break;
			}
			break;
		case 1:
			LPC_SCU->PINTSEL0 = ((portNum<<13)|(bitValue<<8));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<1);
					LPC_GPIO_PIN_INT->IENR |= 1<<1;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<1);
					LPC_GPIO_PIN_INT->IENF |= 1<<1;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<1;
					LPC_GPIO_PIN_INT->IENR |= 1<<1;
					LPC_GPIO_PIN_INT->SIENF |= 1<<1;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<1;
					LPC_GPIO_PIN_INT->IENR |= 1<<1;
					LPC_GPIO_PIN_INT->CIENF |= 1<<1;
					break;
				default:
					break;
			}
			break;
		case 2:
			LPC_SCU->PINTSEL0 = ((portNum<<21)|(bitValue<<16));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<2);
					LPC_GPIO_PIN_INT->IENR |= 1<<2;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<2);
					LPC_GPIO_PIN_INT->IENF |= 1<<2;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<2;
					LPC_GPIO_PIN_INT->IENR |= 1<<2;
					LPC_GPIO_PIN_INT->SIENF |= 1<<2;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<2;
					LPC_GPIO_PIN_INT->IENR |= 1<<2;
					LPC_GPIO_PIN_INT->CIENF |= 1<<2;
					break;
				default:
					break;
			}
			break;
		case 3:
			LPC_SCU->PINTSEL0 = ((portNum<<29)|(bitValue<<24));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<3);
					LPC_GPIO_PIN_INT->IENR |= 1<<3;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<3);
					LPC_GPIO_PIN_INT->IENF |= 1<<3;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<3;
					LPC_GPIO_PIN_INT->IENR |= 1<<3;
					LPC_GPIO_PIN_INT->SIENF |= 1<<3;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<3;
					LPC_GPIO_PIN_INT->IENR |= 1<<3;
					LPC_GPIO_PIN_INT->CIENF |= 1<<3;
					break;
				default:
					break;
			}
			break;
		case 4:
			LPC_SCU->PINTSEL1 = ((portNum<<5)|(bitValue));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<4);
					LPC_GPIO_PIN_INT->IENR |= 1<<4;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<4);
					LPC_GPIO_PIN_INT->IENF |= 1<<4;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<4;
					LPC_GPIO_PIN_INT->IENR |= 1<<4;
					LPC_GPIO_PIN_INT->SIENF |= 1<<4;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<4;
					LPC_GPIO_PIN_INT->IENR |= 1<<4;
					LPC_GPIO_PIN_INT->CIENF |= 1<<4;
					break;
				default:
					break;
			}
		case 5:
			LPC_SCU->PINTSEL1 = ((portNum<<13)|(bitValue<<8));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<5);
					LPC_GPIO_PIN_INT->IENR |= 1<<5;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<5);
					LPC_GPIO_PIN_INT->IENF |= 1<<5;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<5;
					LPC_GPIO_PIN_INT->IENR |= 1<<5;
					LPC_GPIO_PIN_INT->SIENF |= 1<<5;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<5;
					LPC_GPIO_PIN_INT->IENR |= 1<<5;
					LPC_GPIO_PIN_INT->CIENF |= 1<<5;
					break;
				default:
					break;
			}
			break;
		case 6:
			LPC_SCU->PINTSEL1 = ((portNum<<21)|(bitValue<<16));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<6);
					LPC_GPIO_PIN_INT->IENR |= 1<<6;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<6);
					LPC_GPIO_PIN_INT->IENF |= 1<<6;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<6;
					LPC_GPIO_PIN_INT->IENR |= 1<<6;
					LPC_GPIO_PIN_INT->SIENF |= 1<<6;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<6;
					LPC_GPIO_PIN_INT->IENR |= 1<<6;
					LPC_GPIO_PIN_INT->CIENF |= 1<<6;
					break;
				default:
					break;
			}
			break;
		case 7:
			LPC_SCU->PINTSEL1 = ((portNum<<29)|(bitValue<<24));
			switch(intMode)
			{
				case 0://rising edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<7);
					LPC_GPIO_PIN_INT->IENR |= 1<<7;
					break;
				case 1://falling edge
					LPC_GPIO_PIN_INT->ISEL &= ~(1<<7);
					LPC_GPIO_PIN_INT->IENF |= 1<<7;
					break;
				case 2://active High level
					LPC_GPIO_PIN_INT->ISEL |= 1<<7;
					LPC_GPIO_PIN_INT->IENR |= 1<<7;
					LPC_GPIO_PIN_INT->SIENF |= 1<<7;
					break;
				case 3://active Low level
					LPC_GPIO_PIN_INT->ISEL |= 1<<7;
					LPC_GPIO_PIN_INT->IENR |= 1<<7;
					LPC_GPIO_PIN_INT->CIENF |= 1<<7;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}


/*********************************************************************//**
 * @brief		Get GPIO Interrupt Status
 * @param[in]	pintNum	Pin interrupt number, should be: 0 to 7
 * @return		Function status,	could be:
 * 					- ENABLE	:Interrupt has been generated due to a rising edge on P0.0
 * 					- DISABLE	:A rising edge has not been detected on P0.0
 **********************************************************************/
FunctionalState GPIO_GetIntStatus(uint32_t pintNum)
{
	return (FunctionalState)(((LPC_GPIO_PIN_INT->IST)>>pintNum)& 0x1);
}


/*********************************************************************//**
 * @brief		Clear GPIO interrupt status
 * @param[in]	intMode Interrupt mode, should be:
 * 					- 0: Rising edge interrupt mode
 * 					- 1: Falling edge interrupt mode
 * 					- 2: Active-High interrupt mode
 * 					- 3: Active-Low interrupt mode
 * @param[in]	pintNum Pin interrupt number, should be: 0 to 7
 * @return		None
 **********************************************************************/
void GPIO_ClearInt(uint8_t intMode, uint32_t pintNum)
{
	if (!(intMode&(1<<1)))
			LPC_GPIO_PIN_INT->IST = pintNum;
}
#endif


/* FIO word accessible ----------------------------------------------------------------- */
/* Stub function for FIO (word-accessible) style */

/**
 * @brief The same with GPIO_SetDir()
 */
void FIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
{
	GPIO_SetDir(portNum, bitValue, dir);
}

/**
 * @brief The same with GPIO_SetValue()
 */
void FIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	GPIO_SetValue(portNum, bitValue);
}

/**
 * @brief The same with GPIO_ClearValue()
 */
void FIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	GPIO_ClearValue(portNum, bitValue);
}

/**
 * @brief The same with GPIO_ReadValue()
 */
uint32_t FIO_ReadValue(uint8_t portNum)
{
	return (GPIO_ReadValue(portNum));
}


#ifdef GPIO_INT
/**
 * @brief The same with GPIO_IntCmd()
 */
void FIO_IntCmd(uint8_t portNum, uint32_t bitValue, uint8_t edgeState)
{
	GPIO_IntCmd(portNum, bitValue, edgeState);
}

/**
 * @brief The same with GPIO_GetIntStatus()
 */
FunctionalState FIO_GetIntStatus(uint8_t portNum, uint32_t pinNum, uint8_t edgeState)
{
	return (GPIO_GetIntStatus(portNum, pinNum, edgeState));
}

/**
 * @brief The same with GPIO_ClearInt()
 */
void FIO_ClearInt(uint8_t portNum, uint32_t bitValue)
{
	GPIO_ClearInt(portNum, bitValue);
}
#endif


/*********************************************************************//**
 * @brief		Set mask value for bits in FIO port
 * @param[in]	portNum	Port number, in range from 0 to 4
 * @param[in]	bitValue Value that contains all bits in to set, should be
 * 				in range from 0 to 0xFFFFFFFF.
 * @param[in]	maskValue	Mask value contains state value for each bit:
 * 					- 0	:not mask.
 * 					- 1	:mask.
 * @return		None
 *
 * Note:
 * - All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 * - After executing this function, in mask register, value '0' on each bit
 * enables an access to the corresponding physical pin via a read or write access,
 * while value '1' on bit (masked) that corresponding pin will not be changed
 * with write access and if read, will not be reflected in the updated pin.
 **********************************************************************/
void FIO_SetMask(uint8_t portNum, uint32_t bitValue, uint8_t maskValue)
{
		if (maskValue)
		{
		LPC_GPIO_PORT->MASK[portNum] |= bitValue;
	} else
		{
		LPC_GPIO_PORT->MASK[portNum] &= ~bitValue;
	}
}

/**
 * @}
 */

#endif /* _GPIO */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
