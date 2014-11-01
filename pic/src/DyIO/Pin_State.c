/*
 * Pin_State.c
 *
 *  Created on: Nov 23, 2009
 *      Author: hephaestus
 */
#include "UserApp.h"

char					LockCode[5];
char 					Name[17];
char defaultName[] = "DyIO Module";
char defaultlock[] = "0000";

extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
void InitPins(void){
	int i;
	//println_W("Pin Functions");
	InitPinFunction();
	//println_W("Pin States");
	InitPinStates();
	//println_W("Done with Pin States");

	FlashGetMac(MyMAC.v);
	FlashGetName(Name);
        if(Name[0]==0xff){
                for(i=0;i<17;i++){
			Name[i]=defaultName[i] ;
		}
                FlashSetName(Name);
		FlashGetName(Name);
	}

	if (!GetLockCode(LockCode)){
		for(i=0;i<4;i++){
                    LockCode[i] = defaultlock[i];
                }
		SetLockCode(LockCode);
	}


}
