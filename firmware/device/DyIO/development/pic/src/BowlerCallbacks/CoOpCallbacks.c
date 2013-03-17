/*
 * UserMain.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"


void UserRun(void){

	// Run the Bowler Stack Namespace iteration of all async packets
	// Pass in  the function pointer to push the packets upstream
	RunNamespaceAsync(&PutBowlerPacket);



}

