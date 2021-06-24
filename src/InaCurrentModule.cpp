#include <Arduino.h>
#include <Adafruit_INA219.h>
#include <Wire.h>
#include <vacbot_msgs/MotorCurrent.h>
#include "InaCurrentModule.h"
#include <ros.h>

Adafruit_INA219 inaL(INA219_ADDRESS);
Adafruit_INA219 inaR(INA219_ADDRESS+1);

ros::NodeHandle * ina_nh;
vacbot_msgs::MotorCurrent mc_message;
ros::Publisher mc_pub("motor_current", &mc_message);

void task_ina_current_sens() {
    float l = inaL.getCurrent_mA();
    float r = inaR.getCurrent_mA();
    mc_message.header.stamp = ina_nh->now();
    mc_message.current_l = l;
    mc_message.current_r = r;
    mc_pub.publish(&mc_message);
}



void init_ina_current_sens(TwoWire* i2c, ros::NodeHandle *_nh) {
    ina_nh = _nh;
    ina_nh->advertise(mc_pub);
    inaL.begin(i2c);
    inaR.begin(i2c);
    inaL.setCalibration_16V_400mA();
    inaR.setCalibration_16V_400mA();
}