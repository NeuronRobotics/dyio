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

#ifndef PWM_H_
#define PWM_H_

void ClearPWM(uint8_t pin);
uint8_t InitPWM(uint8_t channel);
void SetPWM(uint8_t channel,uint8_t val);
uint8_t GetPWM(uint8_t pin);
#endif /* PWM_H_ */
