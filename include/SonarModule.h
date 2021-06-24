#pragma once
#include <ros.h>
#include <Wire.h>

void init_sonar_ros(TwoWire* i2c, ros::NodeHandle *_nh);
void task_sonar_ros();