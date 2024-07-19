/*
 * local_planner.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "local_planner.h"

float deltaTime = 0.001;
/* global param */
float botPositionX = 0;
float botPositionY = 0;
float goalDistanceX;
float goalDistanceY;

/* function param*/
float xVelocityNow, yVelocityNow, zVelocityNow;
float xMoved = 0, yMoved = 0;
float remainX = goalDistanceX;
float remainY = goalDistanceY;
float lastRemainX = goalDistanceX;
float lastRemainY = goalDistanceY;

void cmd_vel_pub(float Vx_, float Vy_, float W_){
	Vx = (double)Vx_;
	Vy = (double)Vy_;
	W = (double)W_;
}

void pointToDist(const float xGoal, const float yGoal){
    goalDistanceX = xGoal - botPositionX;
    goalDistanceY = yGoal - botPositionY;
    return;
}

void initParam(){
	cmd_vel_pub(0,0,0);
    xMoved = 0, yMoved = 0;
    remainX = lastRemainX = goalDistanceX;
    remainY = lastRemainY = goalDistanceY;
}

// TODO: TF !!!
// Transfer the world coordinate into robot coordinate
float TF_World_to_Robot(float World){
	float Robot = 0.0;
	Robot = World;
	return Robot;
}

// Return if it's arrived or not
int moveTo(){
	float VelX, VelY, AngVelW;
	int is_arrived = 0;
    if (abs(remainX) > 0.001/* && abs(lastRemainX) >= abs(remainX)*/){
        xMoved += rVx * deltaTime;
        lastRemainX = remainX;
        remainX = goalDistanceX - xMoved;
        if (abs(xMoved) <= distance_p_control_0)
            xVelocityNow = velocity_p_control_0;
        else if (abs(xMoved) <= distance_p_control_1)
            xVelocityNow = velocity_p_control_1;
        else if (abs(xMoved) <= distance_p_control_2)
            xVelocityNow = velocity_p_control_2;
        else if (abs(remainX) <= distance_p_control_0)
            xVelocityNow = velocity_p_control_0;
        else if (abs(remainX) <= distance_p_control_1)
            xVelocityNow = velocity_p_control_1;
        else if (abs(remainX) <= distance_p_control_2)
            xVelocityNow = velocity_p_control_2;
        // It's too fast now, so I comment it
        // else if (remainDistance <= distance_p_control_3)
        //     xVelocityNow = velocity_p_control_3;
        else
            xVelocityNow = velocity_p_control_3;

        if (goalDistanceX < 0)
            VelX = -xVelocityNow;
        else
            VelX = xVelocityNow;
        is_arrived = 0;
    }
    else
        VelX = 0;
    if (remainY > 0.001 /*&& abs(lastRemainY) >= abs(remainY)*/){
        yMoved += rVy * deltaTime;
        lastRemainY = remainY;
        remainY = goalDistanceY - yMoved;
        if (yMoved <= distance_p_control_0)
            yVelocityNow = velocity_p_control_0;
        else if (yMoved <= distance_p_control_1)
            yVelocityNow = velocity_p_control_1;
        else if (yMoved <= distance_p_control_2)
            yVelocityNow = velocity_p_control_2;
        else if (remainY <= distance_p_control_0)
            yVelocityNow = velocity_p_control_0;
        else if (remainY <= distance_p_control_1)
            yVelocityNow = velocity_p_control_1;
        else if (remainY <= distance_p_control_2)
            yVelocityNow = velocity_p_control_2;
        // It's too fast now, so I comment it
        // else if (remainY <= distance_p_control_3)
        //     yVelocityNow = velocity_p_control_3;
        else
            yVelocityNow = velocity_p_control_3;

        if (goalDistanceY < 0)
            VelY = -yVelocityNow;
        else
            VelY = yVelocityNow;
        is_arrived = 0;
    }
    else
        VelY = 0;

    if (VelX == 0 && VelY == 0){
    	botPositionX += xMoved;
    	botPositionY += yMoved;
        is_arrived = 1;
    }
    else
        is_arrived = 0;

    AngVelW = 0.0;

    // Go through TF
    VelX = TF_World_to_Robot(VelX);
    VelY = TF_World_to_Robot(VelY);
    AngVelW = TF_World_to_Robot(AngVelW);

    // Publish the cmd_vel
    cmd_vel_pub(VelX, VelY, AngVelW);

    // Return the robot status
    return is_arrived;
}
