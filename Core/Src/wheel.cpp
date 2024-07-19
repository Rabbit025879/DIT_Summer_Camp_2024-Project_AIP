/*
 * wheel.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "wheel.h"

// ** cmd_vel (Interface)
double Vx, Vy, W;
// Required motor_vel
double MF, ML, MR;

// encoder
short enc_MF, enc_MR;
int enc_ML;
// Real motor_vel
double rMF, rML, rMR;
// Real robot_vel
double rVx, rVy, rW;

// ** Interface
// robot_vel(cmd_vel) to motor_vel
//          =  F         ^ y
//        	|            |
//		   / \           |
// 	   L  =   =  R       --------> x
void inverse_kinematics_model(){
	// Calculate cmd_vel into wheel's velocity
	double	WF = -Vx +chassis_radius*W,
			WL = cos60*Vx -cos30*Vy +chassis_radius*W,
			WR = cos60*Vx +cos30*Vy +chassis_radius*W;

	// Calculate wheel's velocity into motor's velocity
	MF = WF/(wheel_radius*(2*pi));
	ML = WL/(wheel_radius*(2*pi));
	MR = WR/(wheel_radius*(2*pi));
}

// motor_vel to robot_vel
void kinematics_model(){
	double rWF = rMF*wheel_radius*(2*pi),
		   rWL = rML*wheel_radius*(2*pi),
		   rWR = rMR*wheel_radius*(2*pi);

	rVx = (-rWF + (rWL + rWR) / cos60) / 3;
	rVy = ((rWR - rWL) / cos30) / 2;
	rW = (rWF + rWL + rWR) / (3 * chassis_radius);
}

void Encoder(){
	//front wheel motor
	enc_MF = -__HAL_TIM_GetCounter(&htim1);
	rMF = (double) enc_MF / (4 * resolution * reductionratio) / motor_span; // revolution/s
	__HAL_TIM_SetCounter(&htim1, 0);

	//left wheel motor
	enc_ML = -__HAL_TIM_GetCounter(&htim2);
	rML = (double) enc_ML / (4 * resolution * reductionratio) / motor_span; // revolution/s
	__HAL_TIM_SetCounter(&htim2, 0);

	//right wheel motor
	enc_MR = __HAL_TIM_GetCounter(&htim3);
	rMR = (double) enc_MR / (4 * resolution * reductionratio) / motor_span; // revolution/s
	__HAL_TIM_SetCounter(&htim3, 0);
}

int pulse_MF, pulse_ML, pulse_MR;
double inte_MF, inte_ML, inte_MR;

void PID_PWM(){
	//PID_MF
	double err_MF = MF - rMF;
	inte_MF += err_MF * motor_span;
	double	bound_MF = 0.01;
	if (ki * inte_MF > 1) inte_MF = bound_MF;
	else if (ki * inte_MF < -1) inte_MF = -bound_MF;
	float u_MF = kp * err_MF + ki * inte_MF;			// pulse
	if (u_MF > 1) u_MF = 1;
	else if (u_MF < -1) u_MF = -1;

	//PWM_MF
	if (u_MF > 0) {
		pulse_MF = (int) (u_MF * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MF_PORT, INA_MF_PIN, GPIO_PIN_SET); // INA
		HAL_GPIO_WritePin(INB_MF_PORT, INB_MF_PIN, GPIO_PIN_RESET); // INB
	} else {
		pulse_MF = (int) (-u_MF * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MF_PORT, INA_MF_PIN, GPIO_PIN_RESET); // INA
		HAL_GPIO_WritePin(INB_MF_PORT, INB_MF_PIN, GPIO_PIN_SET); // INB
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pulse_MF); // PWM

	//PID_ML
	double err_ML = ML - rML;
	inte_ML += err_ML * motor_span;
	double	bound_ML = 0.01;
	if (ki * inte_ML > 1) inte_ML = bound_ML;
	else if (ki * inte_ML < -1) inte_ML = -bound_ML;
	float u_ML = kp * err_ML + ki * inte_ML;			// pulse
	if (u_ML > 1) u_ML = 1;
	else if (u_ML < -1) u_ML = -1;
	//PWM_ML
	if (u_ML > 0) {
		pulse_ML = (int) (u_ML * (motorARR + 1));
		HAL_GPIO_WritePin(INA_ML_PORT, INA_ML_PIN, GPIO_PIN_SET); // INA
		HAL_GPIO_WritePin(INB_ML_PORT, INB_ML_PIN, GPIO_PIN_RESET); // INB
	} else {
		pulse_ML = (int) (-u_ML * (motorARR + 1));
		HAL_GPIO_WritePin(INA_ML_PORT, INA_ML_PIN, GPIO_PIN_RESET); // INA
		HAL_GPIO_WritePin(INB_ML_PORT, INB_ML_PIN, GPIO_PIN_SET); // INB
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pulse_ML); // PWM

	//PID_MR
	double err_MR = MR - rMR;
	inte_MR += err_MR * motor_span;
	double	bound_MR = 0.01;
	if (ki * inte_MR > 1) inte_MR = bound_MR;
	else if (ki * inte_MR < -1) inte_MR = -bound_MR;
	float u_MR = kp * err_MR + ki * inte_MR;			// pulse
	if (u_MR > 1) u_MR = 1;
	else if (u_MR < -1) u_MR = -1;
	//PWM_MR
	if (u_MR > 0) {
		pulse_MR = (int) (u_MR * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MR_PORT, INA_MR_PIN, GPIO_PIN_SET); // INA
		HAL_GPIO_WritePin(INB_MR_PORT, INB_MR_PIN, GPIO_PIN_RESET); // INB
	} else {
		pulse_MR = (int) (-u_MR * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MR_PORT, INA_MR_PIN, GPIO_PIN_RESET); // INA
		HAL_GPIO_WritePin(INB_MR_PORT, INB_MR_PIN, GPIO_PIN_SET); // INB
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pulse_MR); // PWM
}
