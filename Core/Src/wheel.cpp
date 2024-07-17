/*
 * wheel.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "wheel.h"

double WF, WR, WL;
double Vx, Vy, W;
double adjVx = 1.885714;
double adjVy = 0.9637056234718826;
double adjW = 3.922374063966527;
double cmnMF = 1;
double cmnML = 1;
double cmnMR = 1.003;

void inverse_kinematics_model(){

	WR = -0.536*adjVx*Vx -0.027*adjW*W;
	WF = 0.268*adjVx*Vx -0.926*adjVy*Vy -0.027*adjW*W;
	WL = 0.268*adjVx*Vx +0.926*adjVy*Vy -0.027*adjW*W;

	MF = (WF/wheel_radius)/ratio_motor2wheel/(2*pi)*cmnspeed*cmnMF;
	MR = (WR/wheel_radius)/ratio_motor2wheel/(2*pi)*cmnMR*cmnspeed;
	ML = (WL/wheel_radius)/ratio_motor2wheel/(2*pi)*cmnML*cmnspeed;

	}

float inte_rMF = 0;
void Encoder() {
	//front wheel motor
	enc_MF = __HAL_TIM_GetCounter(TIM_ENC_MF);
	rMF = (double) enc_MF / (4 * resolution_MF * reductionratio_MF) / motor_span;//(2*pi);//rev/s = 2Pi/s
	__HAL_TIM_SetCounter(TIM_ENC_MF, 0);

	//right wheel motor
	enc_MR = __HAL_TIM_GetCounter(TIM_ENC_MR);
	rMR = (double) enc_MR / (4 * resolution_MR * reductionratio_MR) / motor_span;//(2*pi);
	__HAL_TIM_SetCounter(TIM_ENC_MR, 0);
	inte_rMF += rMF*motor_span;

	//left wheel motor
	enc_ML = __HAL_TIM_GetCounter(TIM_ENC_ML);
	rML = (-1)*(double) enc_ML / (4 * resolution_ML * reductionratio_ML) / motor_span;//(2*pi);
	__HAL_TIM_SetCounter(TIM_ENC_ML, 0);
}
int pulse_MF;
int pulse_ML;
int pulse_MR;
float u_MF;
void PID_PWM(){

	//PID_MF
	double err_MF = MF - rMF;
	inte_MF += err_MF * motor_span;
	double bound_MF = 1/ki_MF;
	if (ki_MF * inte_MF > 1) inte_MF = bound_MF;
	else if (ki_MF * inte_MF < -1) inte_MF = -bound_MF;
	u_MF = kp_MF * err_MF + ki_MF * inte_MF;
	if (u_MF > 1) u_MF = 1;
	else if (u_MF < -1) u_MF = -1;

	//PWM_MF
	//int pulse_MF;
	if (u_MF > 0) {
		pulse_MF = (int) (u_MF * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MF_PORT, INA_MF_PIN, GPIO_PIN_SET); // INA
		HAL_GPIO_WritePin(INB_MF_PORT, INB_MF_PIN, GPIO_PIN_RESET); // INB
	} else {
		pulse_MF = (int) (-u_MF * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MF_PORT, INA_MF_PIN, GPIO_PIN_RESET); // INA
		HAL_GPIO_WritePin(INB_MF_PORT, INB_MF_PIN, GPIO_PIN_SET); // INB
	}
	__HAL_TIM_SET_COMPARE(TIM_PWM_MF, CH_PWM_MF, pulse_MF); // PWM

	//PID_MR
	double err_MR = MR - rMR;
	inte_MR += err_MR * motor_span;
	double bound_MR = 1/ki_MR;
	if (ki_MR * inte_MR > 1) inte_MR = bound_MR;
	else if (ki_MR * inte_MR < -1) inte_MR = -bound_MR;
	float u_MR = kp_MR * err_MR + ki_MR * inte_MR;
	if (u_MR > 1) u_MR = 1;
	else if (u_MR < -1) u_MR = -1;
	//PWM_MR
	//int pulse_MR;
	if (u_MR > 0) {
		pulse_MR = (int) (u_MR * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MR_PORT, INA_MR_PIN, GPIO_PIN_RESET); // INA
		HAL_GPIO_WritePin(INB_MR_PORT, INB_MR_PIN, GPIO_PIN_SET); // INB
	} else {
		pulse_MR = (int) (-u_MR * (motorARR + 1));
		HAL_GPIO_WritePin(INA_MR_PORT, INA_MR_PIN, GPIO_PIN_SET); // INA
		HAL_GPIO_WritePin(INB_MR_PORT, INB_MR_PIN, GPIO_PIN_RESET); // INB
	}
	__HAL_TIM_SET_COMPARE(TIM_PWM_MR, CH_PWM_MR, pulse_MR); // PWM

	//PID_ML
	double err_ML = ML - rML;
	inte_ML += err_ML * motor_span;
	double bound_ML = 1/ki_ML;
	if (ki_ML * inte_ML > 1) inte_ML = bound_ML;
	else if (ki_ML * inte_ML < -1) inte_ML = -bound_ML;
	float u_ML = kp_ML * err_ML + ki_ML * inte_ML;
	if (u_ML > 1) u_ML = 1;
	else if (u_ML < -1) u_ML = -1;
	//PWM_ML
	//int pulse_ML;
	if (u_ML > 0) {
		pulse_ML = (int) (u_ML * (motorARR + 1));
		HAL_GPIO_WritePin(INA_ML_PORT, INA_ML_PIN, GPIO_PIN_SET); // INA
		HAL_GPIO_WritePin(INB_ML_PORT, INB_ML_PIN, GPIO_PIN_RESET); // INB
	} else {
		pulse_ML = (int) (-u_ML * (motorARR + 1));
		HAL_GPIO_WritePin(INA_ML_PORT, INA_ML_PIN, GPIO_PIN_RESET); // INA
		HAL_GPIO_WritePin(INB_ML_PORT, INB_ML_PIN, GPIO_PIN_SET); // INB
	}
	__HAL_TIM_SET_COMPARE(TIM_PWM_ML, CH_PWM_ML, pulse_ML); // PWM

}

void kinematics_model(){
	double rWL = rMF*ratio_motor2wheel*wheel_radius*(2*pi),
		   rWF = rMR*ratio_motor2wheel*wheel_radius*(2*pi),
		   rWR = rML*ratio_motor2wheel*wheel_radius*(2*pi);

	rVx = (-1.244*rWF + 0.622*rWL + 0.622*rWR)/adjVx;
	rVy = (-0.54*rWL + 0.54*rWR)/adjVy;
	rW = (-12.346*rWF -12.346*rWL -12.346*rWR)/adjW;
}
