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
std::vector<point> pose;
point origin_pose;

// Initialize the path
void path_init(){
	point buffer;
	done = 0;
	origin_pose = {0.2, 0.2, 0.0};
// ** Script
// ------------------------------------------
//	Check Point 1
	buffer = {0.6, 0.25, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.7, 0.3, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Avoid
	buffer = {1.2, 1.10, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Check Point 2
	buffer = {1.3, 1.2, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Avoid
	buffer = {1.6, 1.22, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Check Point 3
	buffer = {1.75, 1.75, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {1.85, 1.85, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	buffer = {1.75, 1.82, 0.0};	// ** Modify path points
//	path.push_back(buffer);		// **
//	buffer = {1.7, 1.8, 0.0};	// ** Modify path points
//	path.push_back(buffer);		// **
//	buffer = {1.82, 1.78, 0.0};	// ** Modify path points
//	path.push_back(buffer);		// **
//	Check Point 4
	buffer = {1.85, 0.25, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	buffer = {1.9, 0.3, 0.0};	// ** Modify path points
//	path.push_back(buffer);		// **
	buffer = {1.75, 0.35, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	buffer = {1.8, 0.2, 0.0};	// ** Modify path points
//	path.push_back(buffer);
	buffer = {1.85, 0.32, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	buffer = {1.8, 0.4, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	Avoid
	buffer = {1.75, 0.6, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {1.5, 1.0, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {1.0, 1.2, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.93, 1.6, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.8, 1.75, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Check Point 5
	buffer = {0.25, 1.75, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.35, 1.85, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.35, 1.75, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.25, 1.85, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Check Point 6 - Encounter obstacle
	buffer = {0.35, 0.95, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.25, 0.85, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	Check Point 6 - Avoid obstacle
//	buffer = {1.0, 1.80, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {1.1, 1.2, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.35, 0.95, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.25, 0.85, 0.0};	// ** Modify path points
//	path.push_back(buffer);
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
