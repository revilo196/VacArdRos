#include "DriveModule.h"
#include "odometry.h"
#include "PwmOut.h"
#include "WheelEncoder.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/Twist.h"
#include "OpticalModule.h"
#define PI 3.14159265358979323846


PwmOut mR1(PA8);
PwmOut mR2(PA9);
PwmOut mL1(PA10);
PwmOut mL2(PA11);
const int encoder_res = 40;
const float wheel_base = 235.0f;
const float wheel_diameter = 52.5f;
const float mm_per_count = (wheel_diameter*PI)/(float)encoder_res;
Odometry odometry(wheel_base);
float errord_linear;
float errord_angular;
float dir_R;
float dir_L;
WheelEncoder encL(PC2);
WheelEncoder encR(PC3);
uint64_t lasttime;
uint64_t lastupdate;
ros::NodeHandle * drive_nh;
geometry_msgs::Twist odo_msg;
geometry_msgs::Twist cmd_vel_msg;
ros::Publisher odo_pub("odometry", &odo_msg );


void cmd_vel_callback(const geometry_msgs::Twist &new_cmd_vel_msg) {
    cmd_vel_msg = new_cmd_vel_msg;
    lastupdate = millis();
}

ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel",&cmd_vel_callback);

float clamp(float value, float min, float max) {
    if (value > max) { return max; }
    if (value < min) { return min; }
    return value;
}

void rightWheel(float f) {
        if (f > 0) {
            mR1 = 0; mR2 = f; dir_R = 1.0f;
        } else {
            mR1 = -f; mR2 = 0; dir_R = -1.0f;
        }
    }

void leftWheel(float f) {
    if (f > 0) {
        mL1 = 0; mL2 = f; dir_L = 1.0f;
    } else {
        mL1 = -f; mL2 = 0; dir_L = -1.0f;
    }
}

void init_drive_ros(ros::NodeHandle * nh) {
    drive_nh = nh;
    drive_nh->advertise(odo_pub);
    drive_nh->subscribe(cmd_vel);
    encL.setup();
    encR.setup();
    errord_linear = 0;
    errord_angular = 0;
}

void task_odometry_ros() {

    if ((millis() - lastupdate)  > 500) {
        cmd_vel_msg = geometry_msgs::Twist();
    }

    u_int64_t current = micros();
    float wR = ((mm_per_count * encR.count()) *0.5f)*dir_R;
    float wL = ((mm_per_count * encL.count()) *0.5f)*dir_L;
    encL.countDiv(1,2); encR.countDiv(1,2); //use low pass filter instad of full reset every time
    odometry.move(wL,wR,current);;

    odo_msg.angular.z = odometry.getRotationSpeed();
    odo_msg.linear.x = odometry.getAvgSpeed();


    odo_pub.publish(&odo_msg);


    float set_linear_vel = cmd_vel_msg.linear.x;
    float set_angular_vel = cmd_vel_msg.angular.z;
    
    float error_linear = set_linear_vel - odometry.getAvgSpeed();
    float error_angular = set_angular_vel - odometry.getRotationSpeed();
    const float maxSpeed = 120.0f; //mm/s aproximate
    const float maxRotation = PI/5.0f;
    //clamp and normalize
    error_linear = clamp(error_linear, -maxSpeed, maxSpeed) / maxSpeed;
    error_angular = clamp(error_angular, -maxRotation, maxRotation) / maxRotation;


    float ctl_R = (error_linear+errord_linear*.2) + (error_angular+errord_angular*.2);
    float ctl_L = (error_linear+errord_linear*.2) - (error_angular+errord_angular*.2);
    errord_angular += error_angular;
    errord_linear += error_linear;
    rightWheel(ctl_R);
    leftWheel(ctl_L);

    lasttime = current;
}

void task_drive_ros() {


}