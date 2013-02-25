/*
 * @brief EEPROM registers and driver functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __EEPROM_001_H_
#define __EEPROM_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_EEPROM_001 IP: EEPROM register block and driver
 * @ingroup IP_Drivers
 * Supports 4032 byte EEPROM devices.
 * @{
 */

/**
 * @brief EEPROM register block structure
 */
typedef struct {				/*!< EEPROM Structure */
	__IO uint32_t CMD;			/*!< EEPROM command register */
	__IO uint32_t ADDR;			/*!< EEPROM address register */
	__IO uint32_t WDATA;		/*!< EEPROM write data register */
	__IO uint32_t RDATA;		/*!< EEPROM read data register */
	__IO uint32_t WSTATE;		/*!< EEPROM wait state register */
	__IO uint32_t CLKDIV;		/*!< EEPROM clock divider register */
	__IO uint32_t PWRDWN;		/*!< EEPROM power-down register */
	uint32_t RESERVED0[975];
	__IO uint32_t ENCLR;		/*!< EEPROM interrupt enable clear */
	__IO uint32_t ENSET;		/*!< EEPROM interrupt enable set */
	__IO uint32_t STAT;			/*!< EEPROM interrupt status */
	__IO uint32_t INTEN;		/*!< EEPROM interrupt enable */
	__IO uint32_t STATCLR;		/*!< EEPROM interrupt status clear */
	__IO uint32_t STATSET;		/*!< EEPROM interrupt status set */
} IP_EEPROM_001_T;

/**
 * @brief Macro defines for EEPROM command register
 */
#define EEPROM_CMD_8_BIT_READ           (0)		/*!< EEPROM 8-bit read command */
#define EEPROM_CMD_16_BIT_READ          (1)		/*!< EEPROM 16-bit read command */
#define EEPROM_CMD_32_BIT_READ          (2)		/*!< EEPROM 32-bit read command */
#define EEPROM_CMD_8_BIT_WRITE          (3)		/*!< EEPROM 8-bit write command */
#define EEPROM_CMD_16_BIT_WRITE         (4)		/*!< EEPROM 16-bit write command */
#define EEPROM_CMD_32_BIT_WRITE         (5)		/*!< EEPROM 32-bit write command */
#define EEPROM_CMD_ERASE_PRG_PAGE       (6)		/*!< EEPROM erase command */

#define EEPROM_CMD_RDPREFETCH           (1 << 3)/*!< EEPROM read pre-fetch enable */

#define EEPROM_PAGE_SIZE                64		/*!< EEPROM byes per page */
#define EEPROM_PAGE_NUM                 63		/*!<  EEPROM pages */

/**
 * @brief Macro defines for EEPROM address register
 */
#define EEPROM_PAGE_OFFSET(n)           (n & 0x3F)
#define EEPROM_PAGE_ADRESS(n)           ((n & 0x3F) << 6)

/**
 * @brief Macro defines for EEPROM write data register
 */
#define EEPROM_WDATA_8_BIT(n)           (n & 0x000000FF)
#define EEPROM_WDATA_16_BIT(n)          (n & 0x0000FFFF)
#define EEPROM_WDATA_32_BIT(n)          (n & 0xFFFFFFFF)

/**
 * @brief Macro defines for EEPROM read data register
 */
#define EEPROM_RDATA_8_BIT(n)           (n & 0x000000FF)
#define EEPROM_RDATA_16_BIT(n)          (n & 0x0000FFFF)
#define EEPROM_RDATA_32_BIT(n)          (n & 0xFFFFFFFF)

/**
 * @brief Macro defines for EEPROM power down register
 */
#define EEPROM_PWRDWN                   (1 << 0)
#define EEPROM_ENDOF_RW                 (26)
#define EEPROM_ENDOF_PROG               (28)

/**
 * @brief EEPROM Mode type definition
 */
typedef enum {
	MODE_8_BIT = 0,
	MODE_16_BIT,
	MODE_32_BIT
} EEPROM_001_Mode_T;

/**
 * @brief	Initializes EEPROM
 * @param	pEEPROM	: pointer to EEPROM peripheral block
 * @param	cclk	: EEPROM base clock rate
 * @return	Nothing
 */
void IP_EEPROM_Init(IP_EEPROM_001_T *pEEPROM, uint32_t cclk);

/**
 * @brief	De-initializes EEPROM
 * @param	pEEPROM	: pointer to EEPROM peripheral block
 * @return	Nothing
 */
STATIC INLINE void IP_EEPROM_DeInit(IP_EEPROM_001_T *pEEPROM)
{
	/* Enable EEPROM power down mode */
	pEEPROM->PWRDWN = 0x1;
}

/**
 * @brief	Write data to EEPROM at specific address
 * @param	pEEPROM			: pointer to EEPROM peripheral block
 * @param	page_offset		: offset of data in page register(0 - 63)
 * @param	page_address	: page address (0-62)
 * @param	data			: buffer that contain data that will be written to buffer
 * @param	mode			: Read mode, should be:
 *                  - MODE_8_BIT    : read 8 bit mode
 *                  - MODE_16_BIT   : read 16 bit mode
 *                  - MODE_32_BIT   : read 32 bit mode
 * @param	size			: number written data (bytes)
 * @return	SUCCESS on successful write of data, or ERROR
 * @note	This function actually write data into EEPROM memory and automatically
 * write into next page if current page is overflowed
 */
Status IP_EEPROM_Write(IP_EEPROM_001_T *pEEPROM,
					   uint16_t page_offset,
					   uint16_t page_address,
					   void *data,
					   EEPROM_001_Mode_T mode,
					   uint32_t size);

/**
 * @brief	Read data to EEPROM at specific address
 * @param	pEEPROM			: pointer to EEPROM peripheral block
 * @param	page_offset		: offset of data in page register(0 - 63)
 * @param	page_address	: page address (0-62)
 * @param	data			: buffer that contain data read from read data register
 * @param	mode			: Read mode, should be:
 *                  - MODE_8_BIT    : read 8 bit mode
 *                  - MODE_16_BIT   : read 16 bit mode
 *                  - MODE_32_BIT   : read 32 bit mode
 * @param	size			: number read data (bytes)
 * @return	Nothing
 */
void IP_EEPROM_Read(IP_EEPROM_001_T *pEEPROM,
					uint16_t page_offset,
					uint16_t page_address,
					void *data,
					EEPROM_001_Mode_T mode,
					uint32_t size);

/**
 * @brief	Erase a page at the specific address
 * @param	pEEPROM			: pointer to EEPROM peripheral block
 * @param	page_address	: EEPROM page address (0-62)
 * @return	Nothing
 */
void IP_EEPROM_Erase(IP_EEPROM_001_T *pEEPROM, uint16_t page_address);

/**
 * @brief	Enable/Disable EEPROM power down mode
 * @param	pEEPROM		: pointer to EEPROM peripheral block
 * @param	NewState	: PowerDown mode state, should be:
 *                  - ENABLE: Enable power down mode
 *                  - DISABLE: Disable power down mode
 * @return	Nothing
 */
void IP_EEPROM_PowerDown(IP_EEPROM_001_T *pEEPROM, FunctionalState NewState);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EEPROM_001_H_ */
