
#ifndef INA_CURRENT_MODULE_H
#define INA_CURRENT_MODULE_H
#include <ros.h>
#include <Wire.h>

void init_ina_current_sens(TwoWire* i2c, ros::NodeHandle *_nh);
void task_ina_current_sens();

#endif