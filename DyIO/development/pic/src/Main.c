/*
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

#if defined(PROGRAMMER_DEBUG)

#if defined(__DEBUG)
    #pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
    //#pragma config POSCMOD = OFF, FNOSC = FRCPLL, FPBDIV = DIV_1
    #pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
    #pragma config FCKSM = CSDCMD, IESO = ON, PWP = OFF
    #pragma config FSOSCEN = OFF, CP = OFF, BWP = OFF, ICESEL = ICS_PGx2
#else
    #define THIS_IS_STACK_APPLICATION
#endif
#endif

#include "Bowler/Bowler.h"
#include "UserApp.h"

/**
 * Main loop
 * 		This is the cooperative main loop
 * Running the main while 1 loop
 * All user code MUST return to the main loop
 * in 5 ms or realtime is broken
 */
int main(void){
	runDyIOMain();
	return 0;
}



