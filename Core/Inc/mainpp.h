/*
 * mainpp.h
 *
 *  Created on: Mar 23, 2023 / Jul 15, 2024 / Jul 17, 2024
 *      Author: kch93 / wang-hsiu-cheng / Tu
 */

// ** Main function

#ifndef INC_MAINPP_H_
#define INC_MAINPP_H_

#include "main.h"
#include "path.h"

#ifdef __cplusplus
extern "C"
{
#endif

void setup();
void main_function();

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

#ifdef __cplusplus
}
#endif

#endif /* INC_MAINPP_H_ */
