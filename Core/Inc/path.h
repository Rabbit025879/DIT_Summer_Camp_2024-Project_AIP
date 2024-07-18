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

#include "local_planner.h"
#include <vector>

struct point{
	double x = 0.0;
	double y = 0.0;
	double w = 0.0;
};

void do_path();

#endif /* INC_PATH_H_ */
