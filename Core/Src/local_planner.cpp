/*
 * local_planner.cpp
 *
 *  Created on: Jul 17, 2024
 *      Author: tu
 */

#include "local_planner.h"

void pointToDist(const float xGoal, const float yGoal){
    goalDistanceX = xGoal - botPositionX;
    goalDistanceY = yGoal - botPositionY;
    return;
}

void initParam(){
    xMoved = 0, yMoved = 0;
    remainX = lastRemainX = goalDistanceX;
    remainY = lastRemainY = goalDistanceY;
}

int moveTo(){
    if (abs(remainX) > 0.001 && abs(lastRemainX) >= abs(remainX)){
        xMoved += realVelX * deltaTime;
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
        return 0;
    }
    else
        VelX = 0;
    if (remainY > 0.001 && abs(lastRemainY) >= abs(remainY)){
        yMoved += realVelY * deltaTime;
        lastRemainY = remainY;
        remainY = goalDistanceX - yMoved;
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
        return 0;
    }
    else
        VelY = 0;

    if (VelX == 0 && VelY == 0)
        return 1;
    else
        return 0;
}


