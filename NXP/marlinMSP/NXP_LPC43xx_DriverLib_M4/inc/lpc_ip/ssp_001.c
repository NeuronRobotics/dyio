/*
 * @brief SSP Registers and control functions
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

#include "ssp_001.h"

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

/*Set up output clocks per bit for SSP bus*/
void IP_SSP_Set_ClockRate(IP_SSP_001_Type *pSSP, uint32_t clk_rate, uint32_t prescale)
{
	pSSP->CR0 &= ~(SSP_CR0_SCR(0xFF));
	pSSP->CR0 |= SSP_CR0_SCR(clk_rate);
	pSSP->CPSR = prescale;
}

/* Enable/Disable SSP operation */
void IP_SSP_Cmd(IP_SSP_001_Type *pSSP, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pSSP->CR1 |= SSP_CR1_SSP_EN;
	}
	else {
		pSSP->CR1 &= (~SSP_CR1_SSP_EN) & SSP_CR1_BITMASK;
	}
}

/* Enable/Disable loopback mode */
void IP_SSP_LoopBackCmd(IP_SSP_001_Type *pSSP, FunctionalState NewState)
{

	if (NewState == ENABLE) {
		pSSP->CR1 |= SSP_CR1_LBM_EN;
	}
	else {
		pSSP->CR1 &= (~SSP_CR1_LBM_EN) & SSP_CR1_BITMASK;
	}
}

/* Enable/Disable interrupt for the SSP */
void IP_SSP_Int_Enable(IP_SSP_001_Type *pSSP, SSP_Int_Mask_Type IntType, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pSSP->IMSC |= IntType;
	}
	else {
		pSSP->IMSC &= (~IntType);
	}
}

#if !defined(CHIP_LPC110X) && !defined(CHIP_LPC11XXLV) && !defined(CHIP_LPC11AXX) && \
	!defined(CHIP_LPC11CXX) && !defined(CHIP_LPC11EXX) && !defined(CHIP_LPC11UXX)
/* Enable/Disable DMA for SSP */
void IP_SSP_DMA_Cmd(IP_SSP_001_Type *pSSP, SSP_DMA_Type ssp_dma_t, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pSSP->DMACR |= ssp_dma_t;
	}
	else {
		pSSP->DMACR &= (~ssp_dma_t);
	}
}

#endif
