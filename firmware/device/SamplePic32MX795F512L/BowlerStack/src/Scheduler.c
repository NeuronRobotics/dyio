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
#include "Bowler/Bowler.h"

#define schedSet 18
#define stepSize (schedSet/6.0)
//RunEveryData sched[]={{0.0,schedSet},{stepSize,schedSet},{stepSize*2,schedSet},{stepSize*3,schedSet},{stepSize*4,schedSet},{stepSize*5,schedSet}};
//
//BYTE SchedulerGetStep(BYTE chan){
//	if(RunEvery(&sched[chan])>0){
//		//sched[chan].MsTime=getMs();
//		return TRUE;
//	}
//	return FALSE;
//
//}
//BYTE ClearForCom(void){
//	return TRUE;
//}
/**
 * RunEvery
 * This function returns not 0 if it has been at least as long as the "setPoint" field says since the last time it returned not 0.
 * All timeing is handeled internally
 * @return float of MS after the assigned time that this function is running. A value of 0 means it has not been long enough
 */

float RunEvery(RunEveryData * data){
    EndCritical();//The interrupts must be running for this to function
	float currentTime;
	float diff;
	currentTime = getMs();
	if(currentTime< data->MsTime)
		data->MsTime=currentTime;//Check and fix overflow
	diff =(currentTime-data->MsTime);
	if (diff > data->setPoint){
		if(data->MsTime+data->setPoint<currentTime)
			data->MsTime = currentTime;
		else
			data->MsTime += data->setPoint;
		return diff-data->setPoint;
	}
	return 0;
}

