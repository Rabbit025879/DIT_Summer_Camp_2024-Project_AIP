/*
 * path.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "path.h"

bool global_planner_on = false;
bool look_ahead_dis_on = false;
std::vector<point> path;

// Do path once
void do_path(){
	point buffer;
	
// ** Script
// ------------------------------------------
	buffer = {1.0, 1.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {1.0, 2.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {3.0, 2.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	buffer = {4.0, 3.0, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {10.0, 3.0, 0.0};	// ** Modify path points
//	path.push_back(buffer);

// ------------------------------------------

	if(global_planner_on)	return;	// TODO: Global planner processing
	if(look_ahead_dis_on)	return;	// TODO: Check for finish
	else{
		while(1){
			if(done)	break;
		}
		return;
	}
}
