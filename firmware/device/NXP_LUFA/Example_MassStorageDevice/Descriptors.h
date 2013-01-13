/*
* Copyright(C) NXP Semiconductors, 2012
* All rights reserved.
*
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
* Permission to use, copy, modify, and distribute this software and its 
* documentation is hereby granted, under NXP Semiconductors' and its 
* licensor's relevant copyrights in the software, without fee, provided that it 
* is used in conjunction with NXP Semiconductors microcontrollers.  This 
* copyright, permission, and disclaimer notice must appear in all copies of 
* this code.
*/



/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_
		#include "USB.h"

	/* Macros: */
		/** Endpoint number of the Mass Storage device-to-host data IN endpoint. */
#if defined(__LPC17XX__)||defined(__LPC177X_8X__)
		#define MASS_STORAGE_IN_EPNUM          5
#else
		#define MASS_STORAGE_IN_EPNUM          3
#endif
		/** Endpoint number of the Mass Storage host-to-device data OUT endpoint. */
		#define MASS_STORAGE_OUT_EPNUM         2

#if defined(__LPC18XX__)||defined(__LPC43XX__)
		/** Size in bytes of the Mass Storage data endpoints. */
		#define MASS_STORAGE_IO_EPSIZE         64
#else
		/** Size in bytes of the Mass Storage data endpoints. */
		#define MASS_STORAGE_IO_EPSIZE         64
#endif

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;

			// Mass Storage Interface
			USB_Descriptor_Interface_t            MS_Interface;
			USB_Descriptor_Endpoint_t             MS_DataInEndpoint;
			USB_Descriptor_Endpoint_t             MS_DataOutEndpoint;
#if defined(USB_DEVICE_ROM_DRIVER) && defined(__LPC11UXX__) || defined(__LPC13UXX__)
			// Required by IP3511 ROM drivers
			unsigned char						  Configuration_Termination;
#endif
		} USB_Descriptor_Configuration_t;

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

