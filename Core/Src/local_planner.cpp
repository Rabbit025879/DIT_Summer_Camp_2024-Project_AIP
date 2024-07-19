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
float xMoved = 0.0, yMoved = 0.0;
float remainX = goalDistanceX;
float remainY = goalDistanceY;
float lastRemainX = goalDistanceX;
float lastRemainY = goalDistanceY;

/* velocity param */
//float maxVelocity = 0.325;
//float vel_0 = 0.05;
//float vel_1 = maxVelocity - 0.05;
//float vel_2 = maxVelocity;

void cmd_vel_pub(float Vx_, float Vy_, float W_)
{
    Vx = (double)Vx_;
    Vy = (double)Vy_;
    W = (double)W_;
}

void pointToDist(const float xGoal, const float yGoal)
{
    goalDistanceX = xGoal - botPositionX;
    goalDistanceY = yGoal - botPositionY;
//    maxVelocity = 0.325;
    // min(min(goalDistanceX, goalDistanceY) / 0.5 * 0.325, 0.325);
//    vel_0 = 0.05;
//    vel_1 = maxVelocity - 0.05;
//    vel_2 = maxVelocity;
    return;
}

void initParam()
{
    cmd_vel_pub(0, 0, 0);
    xMoved = 0.0, yMoved = 0.0;
    remainX = lastRemainX = goalDistanceX;
    remainY = lastRemainY = goalDistanceY;
}

// TODO: TF !!!
// Transfer the world coordinate into robot coordinate

float TF_World_to_Robot(float World)
{
    float Robot = 0.0;
    Robot = World;
    return Robot;
}

// Return if it's arrived or not
int moveTo(){
	float VelX, VelY, AngVelW;
	int is_arrived = 0;
    if (abs(remainX) > 0.01/* && abs(lastRemainX) >= abs(remainX)*/){
        xMoved += rVx * deltaTime;
        lastRemainX = remainX;
        remainX = goalDistanceX - xMoved;
        if (abs(xMoved) <= dist_0)
            xVelocityNow = vel_0;
//            		pow(abs(xMoved) / dist_0, 1.5) * vel_0 + 0.03;
        else if (abs(xMoved) <= dist_1)
            xVelocityNow = (abs(xMoved) - dist_0) * 1.5 + vel_0;
        else if (abs(xMoved) <= dist_2)
            xVelocityNow = pow(((-abs(xMoved) + dist_2) / dist_0), 1.5) * -vel_0 + vel_2;

        else if (abs(remainX) <= dist_0)
            xVelocityNow = pow(abs(remainX) / dist_0, 1.5) * vel_0;
        else if (abs(remainX) <= dist_1)
            xVelocityNow = (abs(remainX) - dist_0) * 1.5 + vel_0;
        else if (abs(remainX) <= dist_2)
            xVelocityNow = pow(((-abs(remainX) + dist_2) / dist_0), 1.5) * -vel_0 + vel_2;
        else
            xVelocityNow = vel_2;

        if (goalDistanceX < 0)
            VelX = -xVelocityNow;
        else
            VelX = xVelocityNow;
        is_arrived = 0;
    }
    else
        VelX = 0;

    if (goalDistanceX != 0)
        VelY = VelX * goalDistanceY / goalDistanceX;
    else if (abs(remainY) > 0.01)
    {
       yMoved += rVy * deltaTime;
       lastRemainY = remainY;
       remainY = goalDistanceY - yMoved;
       if (abs(yMoved) <= dist_0)
           yVelocityNow = pow(abs(yMoved) / dist_0, 1.5) * vel_0 + 0.03;
       else if (abs(yMoved) <= dist_1)
           yVelocityNow = (abs(yMoved) - dist_0) * 1.5 + vel_0;
       else if (abs(yMoved) <= dist_2)
           yVelocityNow = pow(((-abs(yMoved) + dist_2) / dist_0), 1.5) * -vel_0 + vel_2;

       else if (abs(remainY) <= dist_0)
           yVelocityNow = pow(abs(remainY) / dist_0, 1.5) * vel_0;
       else if (abs(remainY) <= dist_1)
           yVelocityNow = (abs(remainY) - dist_0) * 1.5 + vel_0;
       else if (abs(remainY) <= dist_2)
           yVelocityNow = pow(((-abs(remainY) + dist_2) / dist_0), 1.5) * -vel_0 + vel_2;
       else
           yVelocityNow = vel_2;

       if (goalDistanceY < 0)
           VelY = -yVelocityNow;
       else
           VelY = yVelocityNow;
       is_arrived = 0;
   }
    else
        VelY = 0;


    if (abs(rW) > 0.00)
    {
    	AngVelW = -rW * 0.1;
    }
    else
    {
    	AngVelW = 0;
    }

    if (VelX == 0 && VelY == 0){
    	botPositionX += xMoved;
    	botPositionY += yMoved;
        is_arrived = 1;
    }
    else
        is_arrived = 0;


    // Go through TF
    VelX = TF_World_to_Robot(VelX);
    VelY = TF_World_to_Robot(VelY);
    AngVelW = TF_World_to_Robot(AngVelW);

    // Publish the cmd_vel
    cmd_vel_pub(VelX, VelY, AngVelW);

    // Return the robot status
    return is_arrived;
}
