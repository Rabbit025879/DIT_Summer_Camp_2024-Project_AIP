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

// Initialize the path
void path_init(){
	point buffer;
	done = 0;
	
	// ** Script
	// ------------------------------------------
		buffer = {0.3, 0.3, 0.0};	// ** Modify path points
		path.push_back(buffer);
		buffer = {0.3, 0.6, 0.0};	// ** Modify path points
		path.push_back(buffer);
		buffer = {0.6, 0.6, 0.0};	// ** Modify path points
		path.push_back(buffer);
	//	buffer = {4.0, 3.0, 0.0};	// ** Modify path points
	//	path.push_back(buffer);
	//	buffer = {10.0, 3.0, 0.0};	// ** Modify path points
	//	path.push_back(buffer);

	// ------------------------------------------
}

// Do path once
void do_path(){
	path_init();
	if(global_planner_on)	return;	// TODO: Global planner processing
	if(look_ahead_dis_on)	return;	// TODO: Check for finish
	else{
		while(1){
			if(done)	break;
		}
		return;
	}
}
