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
//	----- Straight Test

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
