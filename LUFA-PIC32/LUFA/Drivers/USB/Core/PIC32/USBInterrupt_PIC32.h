/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*

  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief USB Controller Interrupt definitions for the AVR32 UC3 microcontrollers.
 *
 *  This file contains definitions required for the correct handling of low level USB service routine interrupts
 *  from the USB controller.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

#ifndef __USBINTERRUPT_UC3_H__
#define __USBINTERRUPT_UC3_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* External Variables: */
			extern volatile uint32_t USB_Endpoint_SelectedEndpoint;

		/* Enums: */
			enum USB_Interrupts_t
			{
				USB_INT_VBUSTI  = 0,
				#if (defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__))
				USB_INT_IDTI    = 1,
				#endif
				#if (defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__))
				USB_INT_WAKEUPI = 2,
				USB_INT_SUSPI   = 3,
				USB_INT_EORSTI  = 4,
				USB_INT_SOFI    = 5,
				USB_INT_RXSTPI  = 6,
				#endif
				#if (defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__))
				USB_INT_HSOFI   = 7,
				USB_INT_DCONNI  = 8,
				USB_INT_DDISCI  = 9,
				USB_INT_RSTI    = 10,
				USB_INT_BCERRI  = 11,
				USB_INT_VBERRI  = 12,
				#endif
			};

		/* Inline Functions: */
			static inline void USB_INT_Enable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Enable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUSTI:
#warning unimplemented
						break;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
#warning unimplemented
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
#warning unimplemented
						break;
					case USB_INT_SUSPI:
#warning unimplemented
						break;
					case USB_INT_EORSTI:
						U1IEbits.URSTIE = true;
						break;
					case USB_INT_SOFI:
						U1IEbits.SOFIE    = true;
						break;
					case USB_INT_RXSTPI:
						//(&AVR32_USBB.UECON0SET)[USB_Endpoint_SelectedEndpoint].rxstpes = true;
#warning unimplemented
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
#warning unimplemented
						break;
					case USB_INT_DCONNI:
#warning unimplemented
						break;
					case USB_INT_DDISCI:
#warning unimplemented
						break;
					case USB_INT_RSTI:
#warning unimplemented
						break;
					case USB_INT_BCERRI:
#warning unimplemented
						break;
					case USB_INT_VBERRI:
#warning unimplemented
						break;
					#endif
				}
			}

			static inline void USB_INT_Disable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Disable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUSTI:
#warning unimplemented
						break;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
#warning unimplemented
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
#warning unimplemented
						break;
					case USB_INT_SUSPI:
#warning unimplemented
						break;
					case USB_INT_EORSTI:
						U1IEbits.URSTIE = false;
						break;
					case USB_INT_SOFI:
						U1IEbits.SOFIE     			  = false;
						break;
					case USB_INT_RXSTPI:
						//(&AVR32_USBB.UECON0CLR)[USB_Endpoint_SelectedEndpoint].rxstpec = true;
#warning unimplemented
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
#warning unimplemented
						break;
					case USB_INT_DCONNI:
#warning unimplemented
						break;
					case USB_INT_DDISCI:
#warning unimplemented
						break;
					case USB_INT_RSTI:
#warning unimplemented
						break;
					case USB_INT_BCERRI:
#warning unimplemented
						break;
					case USB_INT_VBERRI:
#warning unimplemented
						break;
					#endif
				}
			}

			static inline void USB_INT_Clear(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Clear(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUSTI:
#warning unimplemented
						break;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
#warning unimplemented
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
#warning unimplemented
						break;
					case USB_INT_SUSPI:
#warning unimplemented
						break;
					case USB_INT_EORSTI:
						U1IRbits.URSTIF = false;
						break;
					case USB_INT_SOFI:
						U1IRbits.SOFIF = false;
						break;
					case USB_INT_RXSTPI:
						//(&AVR32_USBB.UESTA0CLR)[USB_Endpoint_SelectedEndpoint].rxstpic = true;
#warning unimplemented
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
#warning unimplemented
						break;
					case USB_INT_DCONNI:
#warning unimplemented
						break;
					case USB_INT_DDISCI:
#warning unimplemented
						break;
					case USB_INT_RSTI:
#warning unimplemented
						break;
					case USB_INT_BCERRI:
#warning unimplemented
						break;
					case USB_INT_VBERRI:
#warning unimplemented
						break;
					#endif
				}
			}

			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUSTI:
#warning unimplemented
						return 0;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
#warning unimplemented
						return 0;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
#warning unimplemented
						return 0;
					case USB_INT_SUSPI:
#warning unimplemented
						return 0;
					case USB_INT_EORSTI:
						return U1IEbits.URSTIE ;
					case USB_INT_SOFI:
						return U1IEbits.SOFIE;
					case USB_INT_RXSTPI:
						//return (&AVR32_USBB.UECON0)[USB_Endpoint_SelectedEndpoint].rxstpe;
#warning unimplemented
						return 0;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
#warning unimplemented
						return 0;
					case USB_INT_DCONNI:
#warning unimplemented
						return 0;
					case USB_INT_DDISCI:
#warning unimplemented
						return 0;
					case USB_INT_RSTI:
#warning unimplemented
						return 0;
					case USB_INT_BCERRI:
#warning unimplemented
						return 0;
					case USB_INT_VBERRI:
#warning unimplemented
						return 0;
					#endif
				}

				return false;
			}

			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUSTI:
#warning unimplemented
						return 0;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
#warning unimplemented
						return 0;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
#warning unimplemented
						return 0;
					case USB_INT_SUSPI:
#warning unimplemented
						return 0;
					case USB_INT_EORSTI:
						return U1IRbits.URSTIF;
					case USB_INT_SOFI:
						return U1IRbits.SOFIF;
					case USB_INT_RXSTPI:
						//return (&AVR32_USBB.UESTA0)[USB_Endpoint_SelectedEndpoint].rxstpi;
#warning unimplemented
						return 0;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
#warning unimplemented
						return 0;
					case USB_INT_DCONNI:
#warning unimplemented
						return 0;
					case USB_INT_DDISCI:
#warning unimplemented
						return 0;
					case USB_INT_RSTI:
#warning unimplemented
						return 0;
					case USB_INT_BCERRI:
#warning unimplemented
						return 0;
					case USB_INT_VBERRI:
#warning unimplemented
						return 0;
					#endif
				}

				return false;
			}

		/* Includes: */
			#include "../USBMode.h"
			#include "../Events.h"
			#include "../USBController.h"

		/* Function Prototypes: */
			void USB_INT_ClearAllInterrupts(void);
			void USB_INT_DisableAllInterrupts(void);
	#endif

	/* Public Interface - May be used in end-application: */
		/* Function Prototypes: */
			#if defined(__DOXYGEN__)
				/** Interrupt service routine handler for the USB controller ISR group. This interrupt routine <b>must</b> be
				 *  linked to the entire USB controller ISR vector group inside the AVR32's interrupt controller peripheral,
				 *  using the user application's preferred USB controller driver.
				 */
				void USB_GEN_vect(void);
			#else
				ISR(USB_GEN_vect);
			#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

