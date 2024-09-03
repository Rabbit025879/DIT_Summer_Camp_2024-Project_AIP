/*
 * local_planner.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "local_planner.h"


float kp_vel = 0.9;
float deltaTime = 0.001;
/* global param */
float botPositionX = 0;
float botPositionY = 0;
float goalDistance;

/* function param*/
float VelocityNow;
float xMoved = 0.0, yMoved = 0.0, wMoved = 0.0, Moved = 0.0;
float remain = goalDistance;
float x_vec, y_vec;
float Goal_w;
float remain_w;

//float maxVelocity = 0.4;
float maxVelocity = 1.0;
float a_bar = 0.0;
float vel_0 = 0.05;
float vel_1 = maxVelocity - 0.05;
float vel_2 = maxVelocity;
float dist_0 = 0.05;
float dist_1 = maxVelocity/1.5 + 0.1/3 - 0.05;
float dist_2 = maxVelocity/1.5 + 0.1/3;

void cmd_vel_pub(float Vx_, float Vy_, float W_)
{
    Vx = (double)Vx_;
    Vy = (double)Vy_;
    W = (double)W_;
}

void pointToDist(const float xGoal, const float yGoal, const float wGoal)
{
    goalDistance = hypot((xGoal - botPositionX),(yGoal - botPositionY));
    x_vec = (xGoal-botPositionX)/goalDistance;
    y_vec = (yGoal-botPositionY)/goalDistance;
    Goal_w = wGoal;
//    goalDistanceY = yGoal - botPositionY;
    maxVelocity = min(goalDistance / 0.5 * 0.325, 0.325);
    vel_0 = 0.05;
    vel_1 = maxVelocity - 0.05;
    vel_2 = maxVelocity;
    dist_0 = 0.05;
    dist_1 = maxVelocity/1.5 + 0.1/3 - 0.05;
    dist_2 = maxVelocity/1.5 + 0.1/3;
    return;
}

void initParam()
{
    cmd_vel_pub(0, 0, 0);
    xMoved = 0.0, yMoved = 0.0;
    remain = goalDistance;
    remain_w = Goal_w - wMoved;
}

// Transfer the world coordinate into robot coordinate
point TF_World_to_Robot(float World_x, float World_y, double Robot_theta){
    point Robot;
    Robot.x = World_x*cos(Robot_theta) + World_y*sin(Robot_theta);
    Robot.y = -World_x*sin(Robot_theta) + World_y*cos(Robot_theta);
    return Robot;
}

// Transfer the robot coordinate into world coordinate
point TF_Robot_to_World(float Robot_x, float Robot_y, double Robot_theta){
    point World;
    World.x = Robot_x*cos(Robot_theta) - Robot_y*sin(Robot_theta);
    World.y = Robot_x*sin(Robot_theta) + Robot_y*cos(Robot_theta);
    return World;
}

// Return if it's arrived or not
int moveTo(){
	float VelX, VelY, AngVelW;
	int is_arrived = 0;
	point world_rVel;
    if (abs(remain) > 0.05/* && abs(lastRemainX) >= abs(remainX)*/){
        world_rVel = TF_Robot_to_World(rVx, rVy, wMoved);
    	xMoved += world_rVel.x * deltaTime;
        yMoved += world_rVel.y * deltaTime;
        Moved = hypot(xMoved, yMoved);
        remain = goalDistance - Moved;

//        if (abs(Moved) <= 0.005)
//        	VelocityNow = 0.05;
//        if (abs(Moved) <= dist_0){
//			VelocityNow = min(VelocityNow, vel_0);
//        }
////            VelocityNow = pow(abs(xMoved) / dist_0, 1.5) * vel_0 ;
//        else if (abs(Moved) <= dist_1)
//            VelocityNow = (abs(Moved) - dist_0) * 1.5 + vel_0 ;
//        else if (abs(Moved) <= dist_2)
//            VelocityNow = pow(((-abs(Moved) + maxVelocity/1.5 + 0.1/3) / dist_0), 1.5) * -vel_0 + maxVelocity;
//
//        else if (abs(remain) <= dist_0)
//            VelocityNow = pow(abs(remain) / dist_0, 1.5) * vel_0 ;
//        else if (abs(remain) <= dist_1)
//            VelocityNow = (abs(remain) - dist_0) * 1.5 + vel_0 ;
//        else if (abs(remain) <= dist_2)
//            VelocityNow = pow(((-abs(remain) + maxVelocity/1.5 + 0.1/3) / dist_0), 1.5) * -vel_0 + maxVelocity;
//        else
//            VelocityNow = vel_2 ;

        if(abs(remain) < 0.06)	kp_vel = 22;
        else if(abs(remain) < 0.07)	kp_vel = 20;
        else if(abs(remain) < 0.12)	kp_vel = 3;
        else kp_vel = 4;
        a_bar += 0.9*deltaTime;
        VelocityNow = kp_vel * remain;
        VelocityNow = min(VelocityNow, a_bar);
        VelocityNow = min(VelocityNow, maxVelocity);

        if (goalDistance < 0){
            VelX = -VelocityNow*x_vec;
        	VelY = -VelocityNow*y_vec;
        }
        else{
            VelX = VelocityNow*x_vec;
            VelY = VelocityNow*y_vec;
        }
        is_arrived = 0;
    } else {
        VelX = 0;
        VelY = 0;
    }
    if(abs(remain_w) > 0.05){
		wMoved += rW * deltaTime;
		remain_w = Goal_w - wMoved;
		AngVelW = remain_w * 0.1745329252;
		min(AngVelW, maxAngularVelocity);
		max(AngVelW, minAngularVelocity);
    } else AngVelW = 0;

    if (VelX == 0 && VelY == 0 && AngVelW == 0){
    	botPositionX += xMoved;
    	botPositionY += yMoved;
        is_arrived = 1;
    }
    else
        is_arrived = 0;

    // Go through TF
    point TF_vel;
	TF_vel = TF_World_to_Robot(VelX, VelY, wMoved);
    VelX = TF_vel.x;
    VelY = TF_vel.y;

    // Publish the cmd_vel
    cmd_vel_pub(VelX, VelY, AngVelW);

    // Return the robot status
    return is_arrived;
}
