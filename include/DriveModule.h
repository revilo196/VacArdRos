#pragma once
#include <ros.h>
//read encoder
//caclulate speed from encoders


//PID speed contoller
//set_point is linear/angular velocity in mm/s
//output is PWM-Signal for L/R-Motor

//get cmd_vel from ros
//put speed caclculation/odometry into ros.



void init_drive_ros(ros::NodeHandle * nh);

void task_odometry_ros();
void task_drive_ros();