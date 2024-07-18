/*
 * TIM_IT.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "TIM_IT.h"

bool reset = false;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM8){
		if(reset)	NVIC_SystemReset();
		inverse_kinematics_model();
		Encoder();
		PID_PWM();
		kinematics_model();
	}
}
