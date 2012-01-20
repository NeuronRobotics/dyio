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

#ifndef LED_H_
#define LED_H_

void SetGreen(WORD Duty);
void SetRed(WORD Duty);
void SetBlue(WORD Duty);
void ToggleGreen(void);
void ToggleRed(void);
void ToggleBlue(void);
void SetColor(WORD r,WORD g,WORD b);

#define ALL_LED (BIT_1 | BIT_2 | BIT_3)
#define red BIT_3
#define green BIT_2
#define blue BIT_1


#endif /* LED_H_ */