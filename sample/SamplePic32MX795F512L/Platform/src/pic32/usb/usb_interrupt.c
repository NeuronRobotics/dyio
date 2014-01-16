/*
 * usb_interrupt.c
 *
 *  Created on: Nov 17, 2011
 *      Author: hephaestus
 */

#include "arch/pic32/USB/usb_fifo.h"

////DOM-IGNORE-END
//#if !defined(__PIC32MX__)
//#define __PIC32MX__
//#endif
//
//
//#if defined(USB_INTERRUPT)
//  #if defined(__18CXX)
//    void USBDeviceTasks(void)
//  #elif defined(__C30__)
//    //void __attribute__((interrupt,auto_psv,address(0xA800))) _USB1Interrupt()
//    void __attribute__((interrupt,auto_psv,nomips16)) _USB1Interrupt()
//  #elif defined(__PIC32MX__)
//    //#pragma interrupt _USB1Interrupt ipl4 vector 45
//    //void __attribute__((nomips16)) _USB1Interrupt( void )
//   void __ISR(_USB_1_VECTOR, ipl4) USB1_ISR(void)
//  #endif
//#else
//void USBDeviceTasks(void)
//#endif
//{
//    //StartCritical();
//    USBDeviceTasks();
//    //EndCritical();
//}
