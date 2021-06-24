#pragma once
#include <ros.h>
#include <Wire.h>


void init_mpu_imu_ros(TwoWire* i2c, ros::NodeHandle *_nh);
void task_mpu_imu_ros();
