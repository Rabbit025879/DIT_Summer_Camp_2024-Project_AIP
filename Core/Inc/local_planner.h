/*
 * local_planner.h
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

// ** Fake Host - Local planner
// ** The path will be process here to publish cmd_vel

#ifndef INC_LOCAL_PLANNER_H_
#define INC_LOCAL_PLANNER_H_

#include "TIM_IT.h"
#include "path_vector_def.h"
#include "wheel.h"
#include <math.h>
using namespace std;

void pointToDist(const float xGoal, const float yGoal, const float wGoal);
void initParam();
int moveTo();
int moveCurve(double radius, double angleRad);
int stop();
point TF_World_to_Robot(float World_x, float World_y, double Robot_theta);
point TF_Robot_to_World(float Robot_x, float Robot_y, double Robot_theta);
void cmd_vel_pub(float Vx_, float Vy_, float W_);

/* p control param */
const float rad_p_control_0 = 0.1745329252;
const float rad_p_control_1 = 0.5235988;
const float rad_p_control_2 = 1.0471976;
const float rad_p_control_3 = 1.57079632679;
const float omega_p_control_0 = 0.087266462599716;
const float omega_p_control_1 = 0.174532925199433;
const float omega_p_control_2 = 0.349065850398866;
const float omega_p_control_3 = 0.523598775598299;
const float maxAngularVelocity = 0.08;
const float minAngularVelocity = 0.05;
//const float maxVelocity = 0.4;
//const float vel_0 = 0.05;
//const float vel_1 = maxVelocity - 0.05;
//const float vel_2 = maxVelocity;
//const float dist_0 = 0.05;
//const float dist_1 = maxVelocity/1.5 + 0.1/3 - 0.05;
//const float dist_2 = maxVelocity/1.5 + 0.1/3;

// cmd_vel
extern double Vx, Vy, W;
// real velocity
extern double rVx, rVy, rW;

#endif /* INC_LOCAL_PLANNER_H_ */
