/*
 * Counter.c
 *
 *  Created on: Feb 7, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

#define ENCIPL ipl1
#define INTPRI EXT_INT_PRI_1
//#define USE_INT_DISABLE

/**
 * this is the storage variable for the counter groups
 */
COUNTER Counter[NUM_COUNTER_GROUPS];
/**
 * This is the mapping between a counter group and its associated DyIO channels
 */
COUNTER_PINS pinmap[]={ {17,16,3},{19,18,2},{21,20,1},{23,22,0}  };

void RunCounter(void){
	uint8_t iIndex;
	//println_I("Running counter");
	for (iIndex=0;iIndex<NUM_COUNTER_GROUPS;iIndex++){
		 runCounterGroup(iIndex);
	}
}

void InitCounterPins(void){
	uint8_t i;
	for (i=0;i< GetNumberOfIOChannels();i++){
		 ClearCounter(i, GetChannelMode(i));
	}
	for (i=0;i<NUM_COUNTER_GROUPS;i++){
		 Counter[i].CURRENT=0;
		 Counter[i].SETPOINT=0;
	}
	OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, (0x1000/10 ));
	ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_5);
    //println_I("Initialized the Counter module");
}
void ClearCounter(uint8_t chan,uint8_t mode){
	uint8_t group = channelToCounterGroup(chan);
	switch ( mode){
		case IS_COUNTER_INPUT_INT:
		case IS_COUNTER_INPUT_DIR:
		case IS_COUNTER_INPUT_HOME:
		case IS_COUNTER_OUTPUT_INT:
		case IS_COUNTER_OUTPUT_DIR:
		case IS_COUNTER_OUTPUT_HOME:
			//println_I("Mode was counter, clearing");
			if(group>0 && (GetChannelMode(0)==IS_SPI_SCK || GetChannelMode(1)==IS_SPI_MISO ||GetChannelMode(2)==IS_SPI_MOSI )){
				SetCoProcMode(0,IS_DI);
				SetCoProcMode(1,IS_DI);
				SetCoProcMode(2,IS_DI);
			}else if(group== 0 && (GetChannelMode(16)==IS_UART_TX ||GetChannelMode(17)==IS_UART_RX )){
				SetCoProcMode(16,IS_DI);
				SetCoProcMode(17,IS_DI);
			}
			SetCoProcMode(pinmap[group].DIR,IS_DI);
			SetCoProcMode(pinmap[group].INT,IS_DI);
			SetCoProcMode(pinmap[group].HOME,IS_DI);
			break;
		default:
			return;
	}
	if (group > 3)
		return;
	//println_I("Clearing counter channel:");p_int_I(group);
	Counter[group].STEP_INDEX=0;
	Counter[group].TimeOffset=0;
	Counter[group].TimeStep=0;
	Counter[group].OutputEnabled=false; 
	Counter[group].Homed=false; 

	switch (group){
	case 0:
		CHAN0P0_tris=INPUT;
		CHAN0P1_tris=INPUT;
		CloseINT1();
		break;
	case 1:
		CHAN1P0_tris=INPUT;
		CHAN1P1_tris=INPUT;
		CloseINT2();
		break;
	case 2:
		CHAN2P0_tris=INPUT;
		CHAN2P1_tris=INPUT;
		CloseINT3();
		break;
	case 3:
		CHAN3P0_tris=INPUT;
		CHAN3P1_tris=INPUT;
		CloseINT4();
		break;
	}

}

void configPin23Int(){
	CHAN3P0_tris=INPUT;
	CHAN3P1_tris=INPUT;
	ConfigINT4(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
	INTEnableSystemMultiVectoredInt();
}

boolean StartCounterInput(uint8_t chan){

	uint8_t group = channelToCounterGroup(chan);
	int64_t count = GetCounterByGroup(group);
	//println_I("Enabeling counter input channel:");p_int_I(group);
	Counter[group].OutputEnabled=false; 
	if (group > 3)
		return false; 
	//println_I("Setting counter output modes");
	if(group>0 && (GetChannelMode(0)==IS_SPI_SCK || GetChannelMode(1)==IS_SPI_MISO ||GetChannelMode(2)==IS_SPI_MOSI )){
		SetCoProcMode(0,IS_DI);
		SetCoProcMode(1,IS_DI);
		SetCoProcMode(2,IS_DI);
	}
	if(group== 0 && (GetChannelMode(16)==IS_UART_TX ||GetChannelMode(17)==IS_UART_RX )){
		SetCoProcMode(16,IS_DI);
		SetCoProcMode(17,IS_DI);
	}
	if(GetChannelMode(pinmap[group].DIR)!=IS_COUNTER_INPUT_DIR)
		SetCoProcMode(pinmap[group].DIR,IS_COUNTER_INPUT_DIR);
	if(GetChannelMode(pinmap[group].INT)!=IS_COUNTER_INPUT_INT)
		SetCoProcMode(pinmap[group].INT,IS_COUNTER_INPUT_INT);
	if(GetChannelMode(pinmap[group].HOME)!=IS_COUNTER_INPUT_HOME)
		SetCoProcMode(pinmap[group].HOME ,IS_COUNTER_INPUT_HOME);

	switch (group){
	case 0:
		CHAN0P0_tris=INPUT;
		CHAN0P1_tris=INPUT;
		ConfigINT1(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
		INTEnableSystemMultiVectoredInt();
		break;
	case 1:
		CHAN1P0_tris=INPUT;
		CHAN1P1_tris=INPUT;
		ConfigINT2(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
		INTEnableSystemMultiVectoredInt();
		break;
	case 2:
		CHAN2P0_tris=INPUT;
		CHAN2P1_tris=INPUT;
		ConfigINT3(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
		INTEnableSystemMultiVectoredInt();
		break;
	case 3:
		configPin23Int();
		break;
	default:
		return false; 
	}
	//This ensures that re-enabeling the interupts doesnt currupt the count
	Counter[group].CURRENT = count;
	Counter[group].Homed=false; 

	return true; 
}
boolean StartCounterOutput(uint8_t chan){
	uint8_t group = channelToCounterGroup(chan);


	if (group > 3)
		return false; 

	if(group>0 && (GetChannelMode(0)==IS_SPI_SCK || GetChannelMode(1)==IS_SPI_MISO ||GetChannelMode(2)==IS_SPI_MOSI )){
		SetCoProcMode(0,IS_DI);
		SetCoProcMode(1,IS_DI);
		SetCoProcMode(2,IS_DI);
	}
	if(group== 0 && (GetChannelMode(16)==IS_UART_TX || GetChannelMode(17)==IS_UART_RX )){
		SetCoProcMode(16,IS_DI);
		SetCoProcMode(17,IS_DI);
	}

	//println_I("Enabeling counter output channel: ");p_int_I(group);
	//println_I("Setting counter input modes");
	if(GetChannelMode(pinmap[group].DIR)!=IS_COUNTER_OUTPUT_DIR)
		SetCoProcMode(pinmap[group].DIR,IS_COUNTER_OUTPUT_DIR);
	if(GetChannelMode(pinmap[group].INT)!=IS_COUNTER_OUTPUT_INT)
		SetCoProcMode(pinmap[group].INT,IS_COUNTER_OUTPUT_INT);
	if(GetChannelMode(pinmap[group].HOME)!=IS_COUNTER_OUTPUT_HOME)
		SetCoProcMode(pinmap[group].HOME ,IS_COUNTER_OUTPUT_HOME);

	Counter[group].OutputEnabled=true; 
	//Counter[chan].SETPOINT= 1000;
	switch (group){
	case 0:
		mPORTEOpenDrainOpen(BIT_7);
		mPORTDOpenDrainOpen(BIT_8);
		CHAN0P0=OFF;
		CHAN0P1=OFF;
		break;
	case 1:
		mPORTEOpenDrainOpen(BIT_6);
		mPORTDOpenDrainOpen(BIT_9);
		CHAN1P0=OFF;
		CHAN1P1=OFF;
		break;
	case 2:
		mPORTEOpenDrainOpen(BIT_5);
		mPORTDOpenDrainOpen(BIT_10);
		CHAN2P0=OFF;
		CHAN2P1=OFF;
		break;
	case 3:
		mPORTEOpenDrainOpen(BIT_4);
		mPORTDOpenDrainOpen(BIT_11);
		CHAN3P0=OFF;
		CHAN3P1=OFF;
		break;
	}
	Counter[group].Homed=false; 
	return true; 
}

void runCounterOutputStep(uint8_t group){
	if (group > 3)
		return;

	if(Counter[group].SETPOINT == Counter[group].CURRENT ){
		return;
	}
	//print_I("Step");
	if (Counter[group].SETPOINT > Counter[group].CURRENT ){
		switch (Counter[group].STEP_INDEX){
		case 0:
			setPinsByGroup(group,ON,ON);
			break;
		case 1:
			setPinsByGroup(group,OFF,ON);
			break;
		case 2:
			setPinsByGroup(group,OFF,OFF);
			break;
		case 3:
			setPinsByGroup(group,ON,OFF);
			break;

		}
		Counter[group].STEP_INDEX +=1;
		if (Counter[group].STEP_INDEX == 4){
			Counter[group].STEP_INDEX = 0;
			Counter[group].CURRENT +=1;
		}

	}else if (Counter[group].SETPOINT < Counter[group].CURRENT ){
		switch (Counter[group].STEP_INDEX){
		case 0:
			setPinsByGroup(group,ON,OFF);
			break;
		case 1:
			setPinsByGroup(group,OFF,OFF);
			break;
		case 2:
			setPinsByGroup(group,OFF,ON);
			break;
		case 3:
			setPinsByGroup(group,ON,ON);
			break;
		}
		Counter[group].STEP_INDEX +=1;
		if (Counter[group].STEP_INDEX == 4){
			Counter[group].STEP_INDEX = 0;
			Counter[group].CURRENT -=1;
		}
	}

	if (Counter[group].TimeStep >= Counter[group].TimeOffset ){
		Counter[group].TimeStep = 0;
	}
	if (Counter[group].STEP_INDEX!=3){
		Counter[group].TimeStep +=1;
	}
}

void runCounterGroup(uint8_t group){
	if (group > 3)
		return;
	switch(GetChannelMode(pinmap[group].INT)){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_OUTPUT_INT:
		break;
	default:
		return;
	}

	//extern uint8_t DIG_val[];

	if ( Counter[group].OutputEnabled == false) {
			if ((GetDigitalValFromAsync(pinmap[group].HOME)==0) ){
				if(Counter[group].Homed ==false) {
					print_I("\nHoming INput group: ");p_int_I(group);print_I(" based on DyIO input: ");p_int_I(pinmap[group].HOME);
					Counter[group].Homed=true; 
					if(GetPIDGroup(pinmap[group].INT) != NOT_USED_IN_PID ){
						println_I("Used in PID, pushing async limit event");
						uint8_t g = GetPIDGroup(pinmap[group].INT);
						//SetPID(g,Counter[group].CURRENT);
						trigerPIDLimit(g,INDEXEVENT,Counter[group].CURRENT);
						//Counter[group].SETPOINT=Counter[group].CURRENT;
					}else{
						Counter[group].CURRENT=0;
						Counter[group].SETPOINT=0;
					}
				}

			}else{
				Counter[group].Homed=false; 
			}
	}else{
		if(Counter[group].STEP_INDEX==0){
			if(Counter[group].interpolate.setTime>0)
				Counter[group].SETPOINT = interpolate(&Counter[group].interpolate,getMs());
			else{
				Counter[group].SETPOINT=Counter[group].interpolate.set;
			}

			if ((GetDigitalValFromAsync(pinmap[group].HOME)==0) ){
				if(Counter[group].Homed == false) {
					//print_I("\nHoming OUTput group: ");p_int_I(group);print_I(" based on DyIO input: ");p_int_I(pinmap[group].HOME);
					Counter[group].Homed=true; 
					Counter[group].CURRENT=0;
					Counter[group].SETPOINT=0;
					Counter[group].interpolate.set=(float)0;
					Counter[group].interpolate.setTime=0;
					Counter[group].interpolate.start=0;
					Counter[group].interpolate.startTime=getMs();
				}
			}else{
				Counter[group].Homed=false; 
			}
		}
		runCounterOutputStep(group);
	}
}

void setPinsByGroup(uint8_t group,uint8_t pin1,uint8_t pin2){
	switch (group){
	case 0:
		CHAN0P0=pin1;
		CHAN0P1=pin2;
		break;
	case 1:
		CHAN1P0=pin1;
		CHAN1P1=pin2;
		break;
	case 2:
		CHAN2P0=pin1;
		CHAN2P1=pin2;
		break;
	case 3:
		CHAN3P0=pin1;
		CHAN3P1=pin2;
		break;
	}
}
int64_t GetCounterByGroup(uint8_t group){
	return Counter[group].CURRENT;
}
int64_t GetCounterByChannel(uint8_t channel){
	int64_t val = GetCounterByGroup(channelToCounterGroup(channel));
	uint8_t mode = GetChannelMode(channel);
	if((mode == IS_COUNTER_INPUT_DIR || mode==IS_COUNTER_INPUT_INT) && val<4){
		val-=1;
	}
	return val;
}
int64_t GetCounterOutput(uint8_t chan){
	return Counter[channelToCounterGroup(chan)].CURRENT;
}

boolean SetCounterOutput(uint8_t chan,int64_t val, uint32_t ms){
	uint8_t group =channelToCounterGroup(chan);

	//Counter[group].SETPOINT=val;
	Counter[group].interpolate.set=(float)val;
	Counter[group].interpolate.setTime=ms;
	Counter[group].interpolate.start=Counter[group].CURRENT;
	Counter[group].interpolate.startTime=getMs();

	return true; 
}
boolean SetCounterInput(uint8_t chan,int64_t val){
	Counter[channelToCounterGroup(chan)].CURRENT=val;
	return true; 
}

uint8_t channelToCounterGroup(uint8_t chan){
	uint8_t i;
	for(i=0;i<NUM_COUNTER_GROUPS;i++){
		if(pinmap[i].INT == chan || pinmap[i].DIR == chan ||pinmap[i].HOME == chan )
			return i;
	}
	return 0xff;
}

uint8_t getCounterIntChannnel(uint8_t group){
	return pinmap[group].INT;
}
uint8_t getCounterDirChannnel(uint8_t group){
	return pinmap[group].DIR;
}
uint8_t getCounterHomeChannnel(uint8_t group){
	return pinmap[group].HOME;
}

void __ISR(_EXTERNAL_1_IRQ, ENCIPL) INT1_ISR(void){
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN0P1){
		mINT1SetEdgeMode(0);
		//ConfigINT4(EXT_INT_ENABLE | FALLING_EDGE_INT | EXT_INT_PRI_5);
		if (CHAN0P0)
			Counter[0].CURRENT++;
		else
			Counter[0].CURRENT--;
	}else{
		mINT1SetEdgeMode(1);
		//ConfigINT4(EXT_INT_ENABLE | RISING_EDGE_INT | EXT_INT_PRI_5);
		if (!CHAN0P0)
			Counter[0].CURRENT++;
		else
			Counter[0].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT1ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}

void __ISR(_EXTERNAL_2_IRQ, ENCIPL) INT2_ISR(void){
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN1P1){
		mINT2SetEdgeMode(0);
		if (CHAN1P0)
			Counter[1].CURRENT++;
		else
			Counter[1].CURRENT--;
	}else{
		mINT2SetEdgeMode(1);
		if (!CHAN1P0)
			Counter[1].CURRENT++;
		else
			Counter[1].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT2ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}
void __ISR(_EXTERNAL_3_IRQ, ENCIPL) INT3_ISR(void){
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN2P1){
		mINT3SetEdgeMode(0);
		if (CHAN2P0)
			Counter[2].CURRENT++;
		else
			Counter[2].CURRENT--;
	}else{
		mINT3SetEdgeMode(1);
		if (!CHAN2P0)
			Counter[2].CURRENT++;
		else
			Counter[2].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT3ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}
void __ISR(_EXTERNAL_4_IRQ, ENCIPL) INT4_ISR(void){


	if(GetChannelMode(23)==IS_PPM_IN){
		runPPMEvent();
		mINT4ClearIntFlag();
		return;
	}
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN3P1){
		mINT4SetEdgeMode(0);
		if (CHAN3P0)
			Counter[3].CURRENT++;
		else
			Counter[3].CURRENT--;
	}else{
		mINT4SetEdgeMode(1);
		if (!CHAN3P0)
			Counter[3].CURRENT++;
		else
			Counter[3].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT4ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}

void __ISR(_TIMER_3_VECTOR, ipl5) _Timer3Handler(void)
{
	//StartCritical();
	ConfigIntTimer3(T3_INT_OFF);
	mT3ClearIntFlag();
	RunCounter();
	ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_5);
	//EndCritical();
}



