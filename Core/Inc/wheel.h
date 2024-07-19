/*
 * wheel.h
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

// ** Wheel control
// ** The cmd_vel will be process here to control the motor
// ** Interface -> Vx, Vy, W (cmd_vel)

#ifndef INC_WHEEL_H_
#define INC_WHEEL_H_

#include "TIM_IT.h"

// Math constant
#define pi 3.14159265359
#define cos60 0.5
#define cos30 0.866025403784439

// Motor data sheet
#define resolution 256
#define reductionratio 24

// Motor control
#define motor_span 0.001
#define kp 2.2
#define ki 20.5

// Motor PWM output
#define motorARR 999 //ARR of TIM4

// Chassis data
#define chassis_radius 0.1695 	// meter
#define wheel_radius 0.029 	// meter

// Pin names
// MF
#define INA_MF_PORT GPIOC
#define INA_MF_PIN GPIO_PIN_6
#define INB_MF_PORT GPIOC
#define INB_MF_PIN GPIO_PIN_7
// ML
#define INA_ML_PORT GPIOC
#define INA_ML_PIN GPIO_PIN_8
#define INB_ML_PORT GPIOC
#define INB_ML_PIN GPIO_PIN_9
// MR
#define INA_MR_PORT GPIOA
#define INA_MR_PIN GPIO_PIN_8
#define INB_MR_PORT GPIOA
#define INB_MR_PIN GPIO_PIN_9

void inverse_kinematics_model();
void kinematics_model();
void Encoder();
void PID_PWM();

#endif /* INC_WHEEL_H_ */
