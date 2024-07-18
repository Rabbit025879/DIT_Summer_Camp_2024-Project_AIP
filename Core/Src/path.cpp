/*
 * path.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "path.h"

bool global_planner_on = false;
bool look_ahead_dis_on = false;

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

// ------------------------------------------

	int which_point = 0;
	if(global_planner_on)	return;	// TODO: Global planner processing
	if(look_ahead_dis_on)	return;	// TODO: Check for finish
	else{
		while(which_point < path.size()-1){
			// Publish the path point one by one
			which_point++;
			if (arrived == 1){
				pointToDist(path[which_point].x, path[which_point].y);
				initParam();
			}
			arrived = moveTo();
			if(arrived)	break;
		}
	}
}
