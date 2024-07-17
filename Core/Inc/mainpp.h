/*
 * mainpp.h
 *
 *  Created on: Mar 23, 2023 / Jul 15, 2024 / Jul 17, 2024
 *      Author: kch93 / wang-hsiu-cheng / Tu
 */

// ** Main function

#ifndef INC_MAINPP_H_
#define INC_MAINPP_H_

#include "path.h"

#ifdef __cplusplus
extern "C"
{
#endif

//motor data sheet
#define resolution 512
#define reductionratio 216

// Update Interrupt
#define TIM_UPD_IT &htim8

//motor control
#define motor_span 0.001

//pin names
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

//motor PWM output
#define motorARR 999 //ARR of TIM4

//dynamics
#define pi 3.14159265359
#define degree60 pi/3
#define degree30 pi/6

#define ratio_motor2wheel 0.5 //motor 1 revolution wheel 32/20 revolution -> 20/40
#define LF 0.1
#define LR 0.1
#define LL 0.1
#define L 0.1
#define wheel_radius 0.03

void setup();
void main_function();
extern double Vx, Vy, W, adjVx, adjVy, adjW, cmnMF, cmnML, cmnMR;
extern float rVx, rVy, rW;

#ifdef __cplusplus
}
#endif

#endif /* INC_MAINPP_H_ */
