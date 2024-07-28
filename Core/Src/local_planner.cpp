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
float goalDistance;

/* function param*/
float VelocityNow;
float xMoved = 0.0, yMoved = 0.0, wMoved = 0.0, Moved = 0.0;
float remain = goalDistance;
float x_vec, y_vec;
float Goal_w;
float remain_w;

float vel_0 = 0.05;
float vel_1 = maxVelocity - 0.05;
float vel_2 = maxVelocity;
float dist_0 = 0.05;
float dist_1 = maxVelocity / 1.5 + 0.1 / 3 - 0.05;
float dist_2 = maxVelocity / 1.5 + 0.1 / 3;

float tempt_constant;
float yaw_0;
float yaw_1;
float yaw_2;
float angle_0;
float angle_1;
float angle_2;

void cmd_vel_pub(float Vx_, float Vy_, float W_)
{
    Vx = (double)Vx_;
    Vy = (double)Vy_;
    W = (double)W_;
}

void pointToDist(const float xGoal, const float yGoal, const float wGoal)
{
    goalDistance = hypot((xGoal - botPositionX), (yGoal - botPositionY));
    x_vec = (xGoal - botPositionX) / goalDistance;
    y_vec = (yGoal - botPositionY) / goalDistance;
    Goal_w = wGoal;
    return;
}

void initParam()
{
    cmd_vel_pub(0, 0, 0);
    xMoved = 0.0, yMoved = 0.0;
    remain = goalDistance;
    remain_w = Goal_w - wMoved;
    // modify params about velocity control
    maxVelocity = min(goalDistance / 0.5 * 0.325, 0.325);
    vel_0 = 0.05;
    vel_1 = maxVelocity - 0.05;
    vel_2 = maxVelocity;
    dist_0 = 0.05;
    dist_1 = maxVelocity / 1.5 + 0.1 / 3 - 0.05;
    dist_2 = maxVelocity / 1.5 + 0.1 / 3;
    // modify params about angular velocity control
    tempt_constant = (Goal_w >= 0.06) ? 0.02 : ((Goal_w >= 0.04) ? 0.01 : 0.005);
    maxYawVel = min((Goal_w / 2 - tempt_constant) * 1.5, maxAngularVelocity);
    yaw_0 = tempt_constant;
    yaw_1 = maxYawVel - tempt_constant;
    yaw_2 = maxYawVel;
    angle_0 = tempt_constant;
    angle_1 = (maxYawVel + tempt_constant) / 1.5 - tempt_constant;
    angle_2 = (maxYawVel + tempt_constant) / 1.5;
}

// Transfer the world coordinate into robot coordinate
point TF_World_to_Robot(float World_x, float World_y, double Robot_theta)
{
    point Robot;
    Robot.x = World_x * cos(Robot_theta) + World_y * sin(Robot_theta);
    Robot.y = -World_x * sin(Robot_theta) + World_y * cos(Robot_theta);
    return Robot;
}

// Transfer the robot coordinate into world coordinate
point TF_Robot_to_World(float Robot_x, float Robot_y, double Robot_theta)
{
    point World;
    World.x = Robot_x * cos(Robot_theta) - Robot_y * sin(Robot_theta);
    World.y = Robot_x * sin(Robot_theta) + Robot_y * cos(Robot_theta);
    return World;
}

// Return if it's arrived or not
int moveTo()
{
    float VelX, VelY, AngVelW;
    int is_arrived = 0;
    point world_rVel;
    if (abs(remain) > 0.005)
    {
        world_rVel = TF_Robot_to_World(rVx, rVy, wMoved);
        xMoved += world_rVel.x * deltaTime;
        yMoved += world_rVel.y * deltaTime;
        Moved = hypot(xMoved, yMoved);
        remain = goalDistance - Moved;

        if (abs(Moved) <= dist_0)
            VelocityNow = vel_0;
        else if (abs(Moved) <= dist_1)
            VelocityNow = (abs(Moved) - dist_0) * 1.5 + vel_0;
        else if (abs(Moved) <= dist_2)
            VelocityNow = pow(((-abs(Moved) + maxVelocity / 1.5 + 0.1 / 3) / dist_0), 1.5) * -vel_0 + maxVelocity;

        else if (abs(remain) <= dist_0)
            VelocityNow = pow(abs(remain) / dist_0, 1.5) * vel_0;
        else if (abs(remain) <= dist_1)
            VelocityNow = (abs(remain) - dist_0) * 1.5 + vel_0;
        else if (abs(remain) <= dist_2)
            VelocityNow = pow(((-abs(remain) + maxVelocity / 1.5 + 0.1 / 3) / dist_0), 1.5) * -vel_0 + maxVelocity;
        else
            VelocityNow = vel_2;

        if (goalDistance < 0)
        {
            VelX = -VelocityNow * x_vec;
            VelY = -VelocityNow * y_vec;
        }
        else
        {
            VelX = VelocityNow * x_vec;
            VelY = VelocityNow * y_vec;
        }
        is_arrived = 0;
    }
    else
    {
        VelX = 0;
        VelY = 0;
    }

    if (abs(remain_w) > 0.01)
    {
        // wMoved += rW * deltaTime;
        // remain_w = Goal_w - wMoved;
        // AngVelW = remain_w * 0.1745329252;
        // min(AngVelW, maxAngularVelocity);
        // max(AngVelW, minAngularVelocity);

        wMoved += rW * deltaTime;
        remain_w = Goal_w - wMoved;

        if (abs(wMoved) <= angle_0)
            AngVelW = yaw_0;
        else if (abs(wMoved) <= angle_0)
            AngVelW = (abs(wMoved) - angle_0) * 1.5 + yaw_0;
        else if (abs(wMoved) <= angle_1)
            AngVelW = pow(((-abs(wMoved) + (maxYawVel + tempt_constant) / 1.5) / angle_0), 1.5) * -yaw_0 + maxYawVel;

        else if (abs(remain_w) <= angle_0)
            AngVelW = pow(abs(remain_w) / angle_0, 1.5) * yaw_0;
        else if (abs(remain_w) <= angle_1)
            AngVelW = (abs(remain_w) - angle_0) * 1.5 + yaw_0;
        else if (abs(remain_w) <= angle_2)
            AngVelW = pow(((-abs(remain_w) + (maxYawVel + tempt_constant) / 1.5) / angle_0), 1.5) * -yaw_0 + maxYawVel;
        else
            AngVelW = yaw_2;
    }
    else
        AngVelW = 0;

    if (VelX == 0 && VelY == 0 && AngVelW == 0)
    {
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
