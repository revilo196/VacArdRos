#include "OpticalModule.h"
#include "Optical.h"
#include <Arduino.h>
#include <vacbot_msgs/OpticalDelta.h>

OpticalSens opti(PB6, PB5,101.0f);

ros::NodeHandle * opt_nh;
vacbot_msgs::OpticalDelta optical_msg;
ros::Publisher optical_pub("optical_delta", &optical_msg);

float speedx, speedy;

void init_optical_ros(ros::NodeHandle *_nh) {
    opt_nh = _nh;
    opti.setup();
    
    for(int i = 0; i < 10; i++) {
        opti.update();
        opti.reset();
        HAL_Delay(100);
    }

    opt_nh->advertise(optical_pub);
}

void task_optical_ros() {
    opti.update();
    float x,y;
    opti.get_mm_xy(x,y);
    float vol;
    optical_msg.header.stamp = opt_nh->now();
    optical_msg.deltaX = x;
    optical_msg.deltaY = y;
    optical_msg.deltaAngle =opti.get_angular_velocity();
    optical_msg.state = opti.image_quality();
    optical_pub.publish(&optical_msg);
}

float get_optical_linear_velocity() {
    return opti.get_velocity();
}
float get_optical_angular_velocity() {
    return opti.get_angular_velocity();
}