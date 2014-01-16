/*
 * ADC.c
 *
 *  Created on: Feb 12, 2010
 *      Author: hephaestus
 */

#include "arch/pic32/BowlerConfig.h"

#include "Bowler/Bowler.h"

float getVoltage(BYTE chan);

int ADCMask = 0;

void InitADCHardware(BYTE chan){

        DDPCONbits.JTAGEN=0;
        AD1CHS = 0x0000;
        AD1PCFG = 0xFFFF;
        AD1CON1 = 0x0000;
        AD1CON2 = 0x0000;
        AD1CON3 = 0x0000;
        AD1CSSL = 0x0000;// Auto Sample only pins that can be ADC
        AD1CHS = 0x0000;
        AD1CON1bits.ASAM = 0;// Enable automatic sampling by setting
        AD1CON1bits.SSRC = 0;
        AD1CON1bits.FORM = 0;			// Output in Integer Format
        AD1CON1bits.ADON = 1;			// Start the ADC module

        AD1CON2bits.VCFG = 0;
        AD1CON2bits.SMPI = 0;// Samples before an interupt
        AD1CON2bits.CSCNA = 0;// Sequentially scan MUXA by setting

        AD1CON3bits.SAMC = 0;// number of A/D clocks between the start of acquisition and the start of conversion
        AD1CON3bits.ADCS = 13;// A/D Conversion clock
        AD1CON3bits.ADRC = 1;// Use RC osscilator for conversion clock by setting
        

        switch(chan){
            case 0:
              ADCMask=  ENABLE_AN0_ANA;
              break;
            case 1:
              ADCMask=  ENABLE_AN1_ANA;
              break;
            case 2:
              ADCMask=  ENABLE_AN2_ANA;
              break;
            case 3:
              ADCMask=  ENABLE_AN3_ANA;
              break;
            case 4:
              ADCMask=  ENABLE_AN4_ANA;
              break;
            case 5:
              ADCMask=  ENABLE_AN5_ANA;
              break;
            case 6:
              ADCMask=  ENABLE_AN6_ANA;
              break;
            case 7:
              ADCMask=  ENABLE_AN7_ANA;
              break;
            case 8:
              ADCMask=  ENABLE_AN8_ANA;
              break;
            case 9:
              ADCMask=  ENABLE_AN9_ANA;
              break;
            case 10:
              ADCMask=  ENABLE_AN10_ANA;
              break;
            case 11:
              ADCMask=  ENABLE_AN11_ANA;
              break;
            case 12:
              ADCMask=  ENABLE_AN12_ANA;
              break;
            case 13:
              ADCMask=  ENABLE_AN13_ANA;
              break;
            case 14:
              ADCMask=  ENABLE_AN14_ANA;
              break;
            case 15:
              ADCMask=  ENABLE_AN15_ANA;
              break;

        }

        mPORTBSetPinsAnalogIn(ADCMask);
        //Use sample channel A
	AD1CHSbits.CH0NA=1;
	EnableADC10();
        //println_I("Initialized ADC chan ");p_int_I(chan);
}
int getAdcRaw(BYTE chan, int samples){
    InitADCHardware( chan);

        int i=0;
        int back = 0;
        do{
            AD1CHSbits.CH0SA = chan;
            AD1CON1bits.SAMP = 1;
            Delay10us(5);
            AD1CON1bits.SAMP = 0;
            while (AD1CON1bits.DONE == 0){
                    // Wait for ADC to finish
            }
            AD1CHS =0;
            back= back + ADC1BUF0;
        }while(i++<samples);

        back = back/(i);
        return back;
}

#define ADC_TO_VOLTS 0.003145631

float getAdcVoltage(BYTE chan, int samples){
         int back = getAdcRaw( chan,  samples);
         
	return ((float)back)*ADC_TO_VOLTS;
}
