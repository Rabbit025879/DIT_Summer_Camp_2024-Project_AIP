/*
 * TIM_IT.h
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

// ** Timer Update Interrupt

#ifndef INC_TIM_IT_H_
#define INC_TIM_IT_H_

#include "main.h"
#include "mainpp.h"
#include "wheel.h"
#include "path.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern std::vector<point> path;

#endif /* INC_TIM_IT_H_ */
