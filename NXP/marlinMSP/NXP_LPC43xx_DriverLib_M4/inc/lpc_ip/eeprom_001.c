/*
 * @brief EEPROM driver functions
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

#include "eeprom_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes EEPROM */
void IP_EEPROM_Init(IP_EEPROM_001_T *pEEPROM, uint32_t cclk)
{
	/* Disable EEPROM power down mode */
	pEEPROM->PWRDWN = 0x0;

	/* Set EEPROM clock to the required 375KHz rate */
	pEEPROM->CLKDIV = (cclk / 375000) - 1;
}

/* Write data to EEPROM at specific address */
Status IP_EEPROM_Write(IP_EEPROM_001_T *pEEPROM,
					   uint16_t page_offset,
					   uint16_t page_address,
					   void *data,
					   EEPROM_001_Mode_T mode,
					   uint32_t count)
{
	uint32_t i;
	uint8_t *tmp8 = (uint8_t *) data;
	uint16_t *tmp16 = (uint16_t *) data;
	uint32_t *tmp32 = (uint32_t *) data;

	pEEPROM->STATCLR = ((1 << EEPROM_ENDOF_RW) | (1 << EEPROM_ENDOF_PROG));

	/* check page_offset */
	if (mode == MODE_16_BIT) {
		if ((page_offset & 0x01) != 0) {
			return ERROR;
		}
	}
	else if (mode == MODE_32_BIT) {
		if ((page_offset & 0x03) != 0) {
			return ERROR;
		}
	}
	pEEPROM->ADDR = EEPROM_PAGE_OFFSET(page_offset);
	for (i = 0; i < count; i++) {
		/* update data to page register */
		if (mode == MODE_8_BIT) {
			pEEPROM->CMD = EEPROM_CMD_8_BIT_WRITE;
			pEEPROM->WDATA = *tmp8;
			tmp8++;
			page_offset += 1;
		}
		else if (mode == MODE_16_BIT) {
			pEEPROM->CMD = EEPROM_CMD_16_BIT_WRITE;
			pEEPROM->WDATA = *tmp16;
			tmp16++;
			page_offset += 2;
		}
		else {
			pEEPROM->CMD = EEPROM_CMD_32_BIT_WRITE;
			pEEPROM->WDATA = *tmp32;
			tmp32++;
			page_offset += 4;
		}
		while (!((pEEPROM->STAT >> EEPROM_ENDOF_RW) & 0x01)) {}
		pEEPROM->STATCLR = (1 << EEPROM_ENDOF_RW);
		if ((page_offset >= EEPROM_PAGE_SIZE) | (i == count - 1)) {
			/* update to EEPROM memory */
			pEEPROM->STATCLR = (0x1 << EEPROM_ENDOF_PROG);
			pEEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address);
			pEEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
			while (!((pEEPROM->STAT >> EEPROM_ENDOF_PROG) & 0x01)) {}
			pEEPROM->STATCLR = (1 << EEPROM_ENDOF_PROG);
		}
		if (page_offset >= EEPROM_PAGE_SIZE) {
			page_offset = 0;
			page_address += 1;
			pEEPROM->ADDR = 0;
			if (page_address > EEPROM_PAGE_NUM - 1) {
				page_address = 0;
			}
		}
	}
	return SUCCESS;
}

/* Read data to EEPROM at specific address */
void IP_EEPROM_Read(IP_EEPROM_001_T *pEEPROM,
					uint16_t page_offset,
					uint16_t page_address,
					void *data,
					EEPROM_001_Mode_T mode,
					uint32_t count)
{
	uint32_t i;
	uint8_t *tmp8 = (uint8_t *) data;
	uint16_t *tmp16 = (uint16_t *) data;
	uint32_t *tmp32 = (uint32_t *) data;

	pEEPROM->STATCLR = ((1 << EEPROM_ENDOF_RW) | (1 << EEPROM_ENDOF_PROG));
	pEEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address) | EEPROM_PAGE_OFFSET(page_offset);
	if (mode == MODE_8_BIT) {
		pEEPROM->CMD = EEPROM_CMD_8_BIT_READ | EEPROM_CMD_RDPREFETCH;
	}
	else if (mode == MODE_16_BIT) {
		pEEPROM->CMD = EEPROM_CMD_16_BIT_READ | EEPROM_CMD_RDPREFETCH;
		/* check page_offset */
		if ((page_offset & 0x01) != 0) {
			return;
		}
	}
	else {
		pEEPROM->CMD = EEPROM_CMD_32_BIT_READ | EEPROM_CMD_RDPREFETCH;
		/* page_offset must be a multiple of 0x04 */
		if ((page_offset & 0x03) != 0) {
			return;
		}
	}

	/* read and store data in buffer */
	for (i = 0; i < count; i++) {

		if (mode == MODE_8_BIT) {
			*tmp8 = (uint8_t) (pEEPROM->RDATA);
			tmp8++;
			page_offset += 1;
		}
		else if (mode == MODE_16_BIT) {
			*tmp16 =  (uint16_t) (pEEPROM->RDATA);
			tmp16++;
			page_offset += 2;
		}
		else {
			*tmp32 = (uint32_t) (pEEPROM->RDATA);
			tmp32++;
			page_offset += 4;
		}
		while (!((pEEPROM->STAT >> EEPROM_ENDOF_RW) & 0x01)) {}
		pEEPROM->STATCLR = (1 << EEPROM_ENDOF_RW);
		if ((page_offset >= EEPROM_PAGE_SIZE) && (i < count - 1)) {
			page_offset = 0;
			page_address++;
			pEEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address) | EEPROM_PAGE_OFFSET(page_offset);
			if (mode == MODE_8_BIT) {
				pEEPROM->CMD = EEPROM_CMD_8_BIT_READ | EEPROM_CMD_RDPREFETCH;
			}
			else if (mode == MODE_16_BIT) {
				pEEPROM->CMD = EEPROM_CMD_16_BIT_READ | EEPROM_CMD_RDPREFETCH;
			}
			else {
				pEEPROM->CMD = EEPROM_CMD_32_BIT_READ | EEPROM_CMD_RDPREFETCH;
			}
		}
	}
}

/* Erase a page at the specific address */
void IP_EEPROM_Erase(IP_EEPROM_001_T *pEEPROM, uint16_t page_address)
{
	uint32_t i;
	uint32_t count = EEPROM_PAGE_SIZE / 4;

	pEEPROM->STATCLR = ((1 << EEPROM_ENDOF_RW) | (1 << EEPROM_ENDOF_PROG));

	/* clear page register */
	pEEPROM->ADDR = EEPROM_PAGE_OFFSET(0);
	pEEPROM->CMD = EEPROM_CMD_32_BIT_WRITE;
	for (i = 0; i < count; i++) {
		pEEPROM->WDATA = 0;
		while (!((pEEPROM->STAT >> EEPROM_ENDOF_RW) & 0x01)) {}
		pEEPROM->STATCLR = (1 << EEPROM_ENDOF_RW);
	}

	pEEPROM->STATCLR = (0x1 << EEPROM_ENDOF_PROG);
	pEEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address);
	pEEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
	while (!((pEEPROM->STAT >> EEPROM_ENDOF_PROG) & 0x01)) {}
	pEEPROM->STATCLR = (1 << EEPROM_ENDOF_PROG);
}

/* Enable/Disable EEPROM power down mode */
void IP_EEPROM_PowerDown(IP_EEPROM_001_T *pEEPROM, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pEEPROM->PWRDWN = 0x1;
	}
	else {
		pEEPROM->PWRDWN = 0x0;
	}
}
