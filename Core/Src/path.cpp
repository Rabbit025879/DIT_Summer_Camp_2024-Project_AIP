/*
 * path.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "path.h"

bool global_planner_on = false;
bool look_ahead_dis_on = false;
point publish_point;

// Do path once
void do_path(){
	point buffer;
	std::vector<point> path;
	
// ** Script
// ------------------------------------------
	int total_points = 5;		// ** Modify total points
	path.reserve(total_points);
	buffer = {0.0, 0.0, 0.0};
	path.push_back(buffer);
	buffer = {1.0, 1.0, 0.0};	// ** Modify path points
	path.push_back(buffer);

// ------------------------------------------

	int which_point = 0;
	if(global_planner_on)	return;	// TODO: Global planner processing
	if(look_ahead_dis_on)	return;	// TODO: Check for finish
	else{
		while(which_point < total_points){
			which_point++;
			publish_point = path[which_point];
		}
	}
}
