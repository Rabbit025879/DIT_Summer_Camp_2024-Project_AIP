///*
// * global_planner.cpp
// *
// *  Created on: Jul 18, 2024
// *      Author: tu
// */
//
//#include "global_planner.h"
//
//void initPath(float distanceArray[pointNumbers][pointNumbers], int pointPath[pointNumbers], int newPointPath[pointNumbers])
//{
//    for (int i = 0; i < pointNumbers; i++)
//        for (int j = 0; j < pointNumbers; j++)
//            distanceArray[i][j] = sqrt(pow((points[i][1] - points[j][1]), 2) + pow((points[i][2] - points[j][2]), 2));
//    for (int i = 0; i < pointNumbers; i++)
//        newPointPath[i] = pointPath[i] = i;
//    return;
//}
//void inverseTwoPoint(int newPointPath[pointNumbers])
//{
//    int num1, num2;
//
//    srand(time(0));
//    num1 = rand() % (pointNumbers - 1) + 1;
//    // Generate the second random number until it is different from the first
//    do
//    {
//        num2 = rand() % (pointNumbers - 1) + 1;
//    } while (num1 == num2);
//
//    swap(newPointPath[num1], newPointPath[num2]);
//    return;
//}
//float calDistance(float distanceArray[pointNumbers][pointNumbers], int newPointPath[pointNumbers])
//{
//    int sum = 0;
//    for (int i = 0; i < pointNumbers - 1; i++)
//        sum += distanceArray[newPointPath[i]][newPointPath[i + 1]];
//    return sum;
//}
//void pointsPlanner()
//{
//    float distanceArray[pointNumbers][pointNumbers];
//    int *newPointPath = new int[pointNumbers];
//    int runs = 50;
//    float r;
//    float delta_f;
//    float temperature = 1;
//    float tempMin = 0.01;
//    float R_t = 0.95;
//    float weight = 0;
//
//    initPath(distanceArray, pointPath, newPointPath);
//
//    while (1)
//    {
//        if (temperature <= tempMin)
//            break;
//        for (int i = 0; i < runs; i++)
//        {
//            inverseTwoPoint(newPointPath);
//            float newWeight = calDistance(distanceArray, newPointPath);
//            delta_f = weight - newWeight;
//            if (delta_f <= 0)
//            {
//                pointPath = newPointPath;
//                weight = newWeight;
//            }
//            else
//            {
//                srand(time(0));
//                float probability = exp(-delta_f / temperature);
//                r = (rand() % 1000) / 1000;
//                if (r < probability)
//                {
//                    pointPath = newPointPath;
//                    weight = newWeight;
//                }
//                else
//                {
//                    pointPath = pointPath;
//                    weight = weight;
//                }
//            }
//        }
//        temperature *= R_t;
//    }
//
//    return;
//}
