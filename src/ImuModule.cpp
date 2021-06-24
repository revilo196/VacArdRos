#include "ImuModule.h"
#include <ros.h>
#include "MPU9250.h"
#include <sensor_msgs/Imu.h>

MPU9250 mpu;
ros::NodeHandle * imu_nh;
sensor_msgs::Imu imu_message;
ros::Publisher imu_pub("imu", &imu_message);

void init_mpu_imu_ros(TwoWire* i2c ,ros::NodeHandle *_nh) {

    MPU9250Setting settings;
    settings.accel_fs_sel = ACCEL_FS_SEL::A4G;
    settings.gyro_fs_sel = GYRO_FS_SEL::G250DPS;
    settings.mag_output_bits = MAG_OUTPUT_BITS::M14BITS;
    settings.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
    settings.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
    settings.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;
    
    if (!mpu.setup(0x68, settings, (*i2c))) {
        //ERRRO
    }

    mpu.calibrateAccelGyro();
    mpu.calibrateMag();

    imu_nh = _nh;
    imu_nh->advertise(imu_pub);

}


void task_mpu_imu_ros() {
   if (mpu.update()) {
        imu_message.header.stamp = imu_nh->now();
        imu_message.linear_acceleration.x = mpu.getLinearAccX();
        imu_message.linear_acceleration.y = mpu.getLinearAccY();
        imu_message.linear_acceleration.z = mpu.getLinearAccZ();
        imu_message.angular_velocity.x = mpu.getGyroX();
        imu_message.angular_velocity.y = mpu.getGyroY();
        imu_message.angular_velocity.z = mpu.getGyroZ();
        imu_message.orientation.x = mpu.getQuaternionX();
        imu_message.orientation.y = mpu.getQuaternionY();
        imu_message.orientation.z = mpu.getQuaternionZ();
        imu_message.orientation.w = mpu.getQuaternionW();
        imu_pub.publish(&imu_message);
   }
}