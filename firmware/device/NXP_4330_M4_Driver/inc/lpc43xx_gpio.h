/**********************************************************************
* $Id$		lpc43xx_gpio.h		2011-06-02
*//**
* @file		lpc43xx_gpio.h
* @brief	Contains all macro definitions and function prototypes
* 			support for GPIO firmware library on lpc43xx
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
/** @defgroup GPIO	GPIO (General Purpose I/O)
 * @ingroup LPC4300CMSIS_FwLib_Drivers
 * @{
 */

#ifndef lpc43xx_GPIO_H_
#define lpc43xx_GPIO_H_

/* Includes ------------------------------------------------------------------- */
#include "lpc43xx.h"
#include "lpc_types.h"

 #define GPIO_PIN_INT
#ifdef __cplusplus
extern "C"
{
#endif

/* Public Macros -------------------------------------------------------------- */
/** @defgroup GPIO_Public_Macros GPIO Public Macros
 * @{
 */

/**
 * @}
 */

/* Public Types --------------------------------------------------------------- */
/** @defgroup GPIO_Public_Types GPIO Public Types
 * @{
 */

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup GPIO_Public_Functions GPIO Public Functions
 * @{
 */

/* GPIO style ------------------------------- */
void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir);
void GPIO_SetValue(uint8_t portNum, uint32_t bitValue);
void GPIO_ClearValue(uint8_t portNum, uint32_t bitValue);
uint32_t GPIO_ReadValue(uint8_t portNum);

#ifdef GPIO_PIN_INT
void GPIO_IntCmd(uint8_t pinInt, uint8_t portNum, uint32_t bitValue, uint8_t intMode);
FunctionalState GPIO_GetIntStatus(uint32_t pintNum);
void GPIO_ClearInt(uint8_t portNum, uint32_t pintNum);
#endif


/* FIO (word-accessible) style ------------------------------- */
void FIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir);
void FIO_SetValue(uint8_t portNum, uint32_t bitValue);
void FIO_ClearValue(uint8_t portNum, uint32_t bitValue);
uint32_t FIO_ReadValue(uint8_t portNum);
void FIO_SetMask(uint8_t portNum, uint32_t bitValue, uint8_t maskValue);

#ifdef GPIO_PIN_INT
void FIO_IntCmd(uint8_t pinInt, uint8_t portNum, uint32_t bitValue, uint8_t intMode);
FunctionalState FIO_GetIntStatus(uint32_t pintNum);
void FIO_ClearInt(uint8_t intMode, uint32_t pintNum);
#endif

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* lpc43xx_GPIO_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
