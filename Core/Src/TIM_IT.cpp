/*
 * TIM_IT.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "TIM_IT.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM8){
		inverse_kinematics_model();
		Encoder();
		PID_PWM();
		kinematics_model();
	}
}
