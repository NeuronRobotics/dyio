/*
 * ChannelValues.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

/**
 * Set Channel Values
 * This function takes a
 * @param pin pin index
 * @param numValues a number of values to be delt with
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
boolean SetChanelValueHW(uint8_t pin, uint8_t numValues, int32_t * data, float ms) {
    uint8_t mode = GetChannelMode(pin);
    int32_t value;

    forceValueDownstream( pin);

	switch (mode) {
		case IS_COUNTER_INPUT_INT:
		case IS_COUNTER_INPUT_DIR:
		case IS_COUNTER_OUTPUT_INT:
		case IS_COUNTER_OUTPUT_DIR:
			SetChanVal(pin, data[0], ms);
			return true;
	}
	if (isSingleByteMode(mode)) {
		int32_t time = ( int32_t ) ms;
		//mask the time into the data byte
		value = (data[0]&0x000000ff) + (time<<16);
//        	println_E("Setting on pin=");p_int_E(pin); print_E(" value= ");p_int_E(value); print_E(" time= ");p_fl_E(ms);
//            println_E(__FILE__);println_E("SetChanelValueHW");
		setDataTableCurrentValue(pin, value);
		return true;
	}
        


    return false; 
}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
boolean GetChanelValueHW(uint8_t pin, uint8_t * numValues, int32_t * data) {
    uint8_t mode = GetChannelMode(pin);

	numValues[0] = 1;
	switch (mode) {
		case IS_COUNTER_INPUT_INT:
		case IS_COUNTER_INPUT_DIR:
			data[0] = GetCounterByChannel(pin);
			return true;
		case IS_COUNTER_OUTPUT_INT:
		case IS_COUNTER_OUTPUT_DIR:
			data[0] = GetCounterOutput(pin);
			return true;
	}
	if (isSingleByteMode(mode)) {
		//mask the time into the data byte
		data[0] = getBcsIoDataTable(pin)->PIN.currentValue;
	}else{
	   data[0] = getBcsIoDataTable(pin)->PIN.currentValue;
	}
	return true;

}

/**
 * Set Channel Values
 * This function takes a
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
boolean SetAllChanelValueHW(int32_t * data, float ms) {
    int i;
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        if (!isStremChannelMode(GetChannelMode(i)))
            SetChanelValueHW(i, 1, & data[i], ms);
    }
    return true; 
}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
boolean GetAllChanelValueHW(int32_t * data) {
    int i;
    uint8_t numValues;
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        if (!isStremChannelMode(GetChannelMode(i)))
            GetChanelValueHW(i, &numValues, & data[i]);
    }
    return true; 
}

/**
 * Configure Channel
 * @param pin the index of the channel to configure
 * @param numValues The number of values passed in to deal with
 * @param data the array of values to use in the configuration step
 */

boolean ConfigureChannelHW(uint8_t pin, uint8_t numValues, int32_t * data) {

	if(GetChannelMode(pin) != 0xff){
		println_E("Loading to hardware ");
					p_int_E(pin);
		SetNewConfigurationDataTable(pin, data[0]);
	}else{
		int i;
		for (i=0;i<numValues;i++){
			data[i]=GetConfigurationDataTable(i);
		}
	}
    return true; 
}

/**
 * Set Stream
 * This function takes a
 * @param pin pin index
 * @param numValues a number of values to be dealt with
 * @param data an array of data values
 *
 */
boolean SetStreamHW(uint8_t pin,uint8_t numValues,uint8_t * data){
	//println_E("Set Stream Stub");
	uint8_t mode = GetChannelMode(pin);

    if (isStremChannelMode(mode)) {
          uint8_t * bData = (uint8_t *) data;
          switch (mode) {
              case IS_SPI_MOSI:
              case IS_SPI_MISO:
              case IS_SPI_SCK:
            	  LoadSPITxData(numValues-1, bData);
                  //SendPacketToSPIFromArray(numValues, bData);
                  return true;
              case IS_UART_TX:
              case IS_UART_RX:
                  LoadSerialTxData(numValues, bData);
                  return true;
              case IS_PPM_IN:
                  ConfigPPMFromArray(bData);
                  return true;
          }
      }

	return true;


}

/**
 * Get Stream
 * This function takes a pin index, a number of values to be dealt with, and an array of data values
 * Data is stored into numValues and data
 */
boolean GetStreamHW(uint8_t pin,uint8_t*  numValues,uint8_t * data){
	//println_E("Get Stream Stub");
	 uint8_t mode = GetChannelMode(pin);
   if (isStremChannelMode(mode)) {
       uint8_t * bData = (uint8_t *) data;
       switch (mode) {
           case IS_SPI_MOSI:
           case IS_SPI_MISO:
           case IS_SPI_SCK:
        	   numValues[0] = GetSPIRxData(bData);
               //SendPacketToSPIFromArray(numValues[0], bData);
               return true;
           case IS_UART_TX:
           case IS_UART_RX:
               numValues[0] = GetSerialRxData(bData);
               return true;
           case IS_PPM_IN:
               numValues[0] = GetPPMDataToArray(bData);
               return true;
       }
   }
	return true;
}

boolean SetChanVal(uint8_t pin, int32_t bval, float time) {
    uint8_t mode = GetChannelMode(pin);
    forceValueDownstream( pin);
    switch (mode) {
        case IS_COUNTER_INPUT_INT:
        case IS_COUNTER_INPUT_DIR:
            println_I("Counter input ");
            printMode(mode, INFO_PRINT);
            SetCounterInput(pin, bval);
            return true; 
        case IS_COUNTER_OUTPUT_INT:
        case IS_COUNTER_OUTPUT_DIR:
            println_I("Counter output ");
            printMode(mode, INFO_PRINT);
            SetCounterOutput(pin, bval, time);
            return true; 
    }
    return true; 
}

