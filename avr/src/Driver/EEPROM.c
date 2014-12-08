/*
 * EEPROM.c
 *
 *  Created on: Feb 17, 2010
 *      Author: hephaestus
 */

#include "UserApp_avr.h"

extern MAC_ADDR MyMAC;

uint8_t eeReadByte(uint16_t addr);
void eeWriteByte(uint16_t addr,uint8_t val);

#define MACKEY 42
#define LOCKKEY 37
#define KEYADDR 0
#define MACSTART 	(KEYADDR+1)
#define MODESTART 	(MACSTART+6)
#define VALUESTART 	(MODESTART+24)
#define UARTBAUD 	(VALUESTART+24)
#define DATASTART_AVR 	(UARTBAUD+4)


void EEInitMAC(void){
	uint8_t i;
	uint8_t key=0;
	key=eeReadByte(KEYADDR);
	if ( (key == LOCKKEY) ){
		for (i=0;i<6;i++){
			MyMAC.v[i]=eeReadByte(i+MACSTART);
		}
	}
}

boolean ProvisionMAC(uint8_t * m){
	uint8_t i;
	uint8_t key=0;
	key=eeReadByte(KEYADDR);
	if (key==LOCKKEY){
		return false; 
	}else{
		for (i=0;i<6;i++){
			MyMAC.v[i]=m[i];
			eeWriteByte(i+MACSTART,MyMAC.v[i]);
		}
		eeWriteByte(KEYADDR,LOCKKEY);
		return true; 
	}
}

void _EEWriteMode(uint8_t pin,uint8_t mode){
	getBcsIoDataTable(pin)->PIN.currentChannelMode = mode;
	if (EEReadMode(pin) != mode){
		//println_W("Mode Set Pin :");p_int_W(pin);printMode(mode,WARN_PRINT);

		eeWriteByte((uint16_t)(MODESTART+pin),mode);
	}
}

uint8_t EEReadMode(uint8_t pin){
	return eeReadByte((uint16_t)(MODESTART+pin));
}


void EEWriteValue(uint16_t pin,uint8_t value){
	if (value == 255)
		value = 254;
	eeWriteByte((uint16_t)(VALUESTART+pin),value);
}

uint8_t EEReadValue(uint16_t pin){
	uint8_t val = eeReadByte((uint16_t)(VALUESTART+pin));
	if (val == 255)
		EEWriteValue(pin,128);
	return eeReadByte((uint16_t)(VALUESTART+pin));
}

uint32_t EEReadBaud(void){
	UINT32_UNION v;
	v.byte.FB= eeReadByte((UARTBAUD+0));
	v.byte.TB= eeReadByte((UARTBAUD+1));
	v.byte.SB= eeReadByte((UARTBAUD+2));
	v.byte.LB= eeReadByte((UARTBAUD+3));
	return v.Val;
}

void EEWriteBaud(uint32_t val){
	UINT32_UNION v;
	v.Val = val;
	eeWriteByte((UARTBAUD+0),v.byte.FB);
	eeWriteByte((UARTBAUD+1),v.byte.TB);
	eeWriteByte((UARTBAUD+2),v.byte.SB);
	eeWriteByte((UARTBAUD+3),v.byte.LB);
}

uint8_t EEReadData(uint16_t addr){
	uint8_t val=0;
	if((addr+DATASTART_AVR)>=1024){
		return 0;
	}
	val =  eeReadByte((DATASTART_AVR+addr));
	if(addr == 189){
		println_W("R eeprom addr: ");p_int_W(addr);print_W(" is: ");p_int_W(val);
	}
	return val;
}
void EEWriteData(uint16_t addr,uint8_t data){
	if((addr+DATASTART_AVR)>=1024){
		return;
	}
	eeWriteByte((DATASTART_AVR+addr),data);
	if(addr == 189){
		println_E("W eeprom addr: ");p_int_W(addr);print_W(" is: ");p_int_W(data);
	}
}


uint8_t eeReadByte(uint16_t addr){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	EECR=0;
	/* Set up address register */
	EEAR = addr;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;

}

void eeWriteByte(uint16_t addr,uint8_t val){
	if (eeReadByte(addr)==val)
		return;
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	EECR=0;
	/* Set up address and Data Registers */
	EEAR = addr;
	EEDR = val;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);

}


