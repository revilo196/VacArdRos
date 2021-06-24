#include "SonarModule.h"
#include "vacbot_msgs/SonarPacket.h"
#include "vacbot_msgs/SonarMin.h"
#include <sstream>
#define M_PI 3.14159265358979323846

TwoWire * sonar_i2c;
ros::NodeHandle * sonar_nh;
vacbot_msgs::SonarPacket sonar_message;
ros::Publisher sonar_pub("sonar", &sonar_message);

#define SEN_CNT 3
uint32_t raw_values[SEN_CNT];
float sensor_angle[SEN_CNT];
volatile uint32_t transfer_buffer[SEN_CNT];



void init_sonar_ros(TwoWire* _i2c, ros::NodeHandle *_nh) {
    sonar_i2c = _i2c;
    sonar_nh = _nh;

    sensor_angle[0] = 0;
    sensor_angle[1] =  -M_PI/4;
    sensor_angle[2] =   M_PI/4;

    

    for(int i = 0; i < SEN_CNT; i++) {
        raw_values[i] = 0;
        transfer_buffer[i] = 0;

        sonar_message.ranges[i].field_of_view=15.0f;
        sonar_message.ranges[i].min_range=70.0f;
        sonar_message.ranges[i].max_range=2000.0f;
        sonar_message.ranges[i].radiation_type = sensor_msgs::Range::ULTRASOUND;
        
    }
    sonar_nh->advertise(sonar_pub);

}


void task_sonar_ros() {
    const uint8_t cmd = 1;
    sonar_i2c->beginTransmission(21);
    sonar_i2c->write(cmd);
    sonar_i2c->endTransmission(false);
    sonar_i2c->requestFrom((uint8_t)21, sizeof(uint32_t) * 3, true);
    sonar_i2c->readBytes( (uint8_t*) raw_values,  sizeof(uint32_t) * 3);

    for(int i = 0; i < SEN_CNT; i++) {
        sonar_message.ranges[i].range = raw_values[i] / 1000.0f;
        sonar_message.ranges[i].header.stamp = sonar_nh->now();
    }

    sonar_pub.publish(&sonar_message);

}