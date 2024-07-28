/*
 * path.h
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

// ** Path script
// ** The Path can be modify here to form a script

#ifndef INC_PATH_H_
#define INC_PATH_H_

#include "path_vector_def.h"
#include "TIM_IT.h"
#include "local_planner.h"

// 定義 PI
constexpr double PI = 3.141592653589793238462643383279502884f;

extern int done;

void path_init();
void do_path();

#endif /* INC_PATH_H_ */
