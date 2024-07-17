/*
 * TIM_IT.h
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

// ** Timer Update Interrupt

#ifndef INC_TIM_IT_H_
#define INC_TIM_IT_H_

void inverse_kinematics_model();
void Encoder();
void PID_PWM();
void kinematics_model();

extern TIM_HandleTypeDef htim8;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIM_IT_H_ */
