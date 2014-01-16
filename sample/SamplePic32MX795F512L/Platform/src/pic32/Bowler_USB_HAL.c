/**
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
// USB values
#include "arch/pic32/BowlerConfig.h"
#include "Bowler/Bowler.h"

#define True TRUE
#define False FALSE

BOOL GetPacketUSB(BYTE * packet,WORD size){
	USBGetArray(packet, size);
	return True;
}
void SendPacketUSB(BYTE * packet,WORD size){
	if (USBPutArray(packet, size)){
		//println_I("Sent to USB");
	}else{
		//println_E("Failed to send to USB");
	}
}


WORD Get_USB_Byte_Count(void){
	return GetNumUSBBytes();
}


