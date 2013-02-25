/*
 * marlinMSP 0.1a - 0.2b System configuration file
 *
 * Core Clock: 204MHZ
 * External Crystal: 12MHZ
 * RTC Crystal: yes
 * Ethernet Crystal: 50MHZ
 * USART Debug Port: USART 1 on Arduino digital lower byte
 *
 *
 */

#ifndef __SYS_CONFIG_H_
#define __SYS_CONFIG_H_


/** @ingroup BOARD_AVR_MARLINMSP_LPC4337_OPTIONS
 * @{
 */

/* Build for 43xx chip family */
#define CHIP_LPC43XX

/* Un-comment DEBUG_ENABLE for IO support via the UART */
#define DEBUG_ENABLE

/* Enable DEBUG_SEMIHOSTING along with DEBUG to enable IO support
   via semihosting */
// #define DEBUG_SEMIHOSTING

/* Board UART used for debug output */
#define DEBUG_UART LPC_USART1

/* Crystal frequency into device */
#define CRYSTAL_MAIN_FREQ_IN 12000000

/* Crystal frequency into device for RTC/32K input */
#define CRYSTAL_32K_FREQ_IN 32768

/* Frequency on external clock in pin */
#define EXTERNAL_CLKIN_FREQ_IN 0

/* Default CPU clock frequency */
#define MAX_CLOCK_FREQ (204000000)

/* Audio and USB default PLL rates (configured in SystemInit()) */
#define CGU_AUDIO_PLL_RATE (0)
#define CGU_USB_PLL_RATE (480000000)

/**
 * @}
 */

#endif /* __SYS_CONFIG_H_ */
