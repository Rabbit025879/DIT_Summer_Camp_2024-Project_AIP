/*
 * path.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "path.h"

bool global_planner_on = false;
bool look_ahead_dis_on = false;
int path_status = 0;	// Life expression Debug
int fake_arrived = 1;	// Life expression Debug

// Do path once
void do_path(){
	point buffer;
	std::vector<point> path;
	int arrived = 1;
	
// ** Script
// ------------------------------------------
	buffer = {0.0, 0.0, 0.0};
	path.push_back(buffer);
	buffer = {1.0, 1.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {2.0, 2.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {3.0, 3.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {3.0, 3.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {3.0, 3.0, 0.0};	// ** Modify path points
	path.push_back(buffer);

// ------------------------------------------

	unsigned int which_point = 0;
	if(global_planner_on)	return;	// TODO: Global planner processing
	if(look_ahead_dis_on)	return;	// TODO: Check for finish
	else{
		while(which_point < path.size()-1){
			// Publish the path point one by one
			fake_arrived = 0;	// Life expression Debug
			HAL_Delay(300);
			arrived = fake_arrived;	// Life expression Debug
			if(arrived == 1){
				which_point++;
				path_status = which_point;	// Life expression Debug
				pointToDist(path[which_point].x, path[which_point].y);
				initParam();
			}
			arrived = moveTo();
		}
		path_status = 999;
		return;
	}
}
