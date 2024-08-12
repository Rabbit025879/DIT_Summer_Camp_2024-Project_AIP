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
point origin_pose;

// Initialize the path
void path_init(){
	point buffer;
	done = 0;
	origin_pose = {0.2, 0.2, 0.0};
// ** Script
// ------------------------------------------
//	----- Straight Test
	buffer = {0.4, 0.2, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.2, 0.2, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.2, 0.4, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.2, 0.2, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.4, 0.4, 0.0};	// ** Modify path points
	path.push_back(buffer);
	buffer = {0.2, 0.2, 0.0};	// ** Modify path points
	path.push_back(buffer);
//	----- Spin
//	buffer = {0.0, 0.0, 0.785};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, 1.57};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, 3.14};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, -3.14};	// ** Modify path points
//	path.push_back(buffer);
//	------ Move and Spin
		// x: 0.2 y:0.2
//	buffer = {0.8, 0.5, 0.785};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {1.3, 0.3, 1.57};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.8, 0.5, 3.14};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	------ Move then Spin
//	buffer = {0.2, 0.2, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.2, 0.2, PI/2};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.1, 0.1, PI/2};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.1, 0.1, PI};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.2, PI};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.2, PI/2};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, PI/2};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.0, 0.0, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	------
//	Map 1 Test path
//	buffer = {1.9, 1.9, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {1.9, 0.2, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.7, 0.2, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.2, 0.9, 0.0};	// ** Modify path points
//	path.push_back(buffer);
//	buffer = {0.2, 1.9, 0.0};	// ** Modify path points
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
