/*
 * mainpp.cpp
 *
 *  Created on: Mar 23, 2023 / Jul 15, 2024 / Jul 17, 2024
 *      Author: kch93 / wang-hsiu-cheng / Tu
 */

#include "mainpp.h"

// STM Setup
void setup(){
	  // Update Interrupt
	  HAL_TIM_Base_Start_IT(&htim8);
	  // Encoder
	  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);	// Front
	  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);
	  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);	// Left
	  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);	// Right
	  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);
	  // PWM
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);	// Front
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);	// Left
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);	// Right
}

void main_function(){
	setup();
	HAL_Delay(1500);
	do_path();
}
