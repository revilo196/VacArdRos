#include <Arduino.h>
// #define _TASK_TIMECRITICAL      // Enable monitoring scheduling overruns
#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
// #define _TASK_WDT_IDS           // Compile with support for wdt control points and task ids
// #define _TASK_LTS_POINTER       // Compile with support for local task storage pointer
// #define _TASK_PRIORITY          // Support for layered scheduling priority
// #define _TASK_MICRO_RES         // Support for microsecond resolution
// #define _TASK_STD_FUNCTION      // Support for std::function (ESP8266 and ESP32 ONLY)
// #define _TASK_DEBUG             // Make all methods and variables public for debug purposes
 #define _TASK_INLINE            // Make all methods "inline" - needed to support some multi-tab, multi-file implementations
// #define _TASK_TIMEOUT           // Support for overall task timeout
// #define _TASK_OO_CALLBACKS      // Support for dynamic callback method binding
#include <TaskScheduler.h>
#include <InaCurrentModule.h>
#include <ImuModule.h>
#include <SonarModule.h>
#include <OpticalModule.h>
#include <DriveModule.h>
#include <Wire.h>

#define LED PB2

// Scheduler
Scheduler ts;
ros::NodeHandle nh;
TwoWire i2c(PB7, PB8);
TwoWire i2c_sonar(PC12,PB10);


void ros_loop() {
  digitalWrite(LED,HIGH);
  nh.spinOnce();
  digitalWrite(LED,LOW);
}

Task task_ros(10*TASK_MILLISECOND, TASK_FOREVER, &ros_loop,&ts,true);
Task task_ina(50*TASK_MILLISECOND, TASK_FOREVER, &task_ina_current_sens, &ts, true);
Task task_imu(20*TASK_MILLISECOND, TASK_FOREVER, &task_mpu_imu_ros, &ts, true);
Task task_sonar(100*TASK_MILLISECOND, TASK_FOREVER, &task_sonar_ros, &ts, true);
Task task_optic(30*TASK_MILLISECOND, TASK_FOREVER, &task_optical_ros, &ts, true);
Task task_drive(200*TASK_MILLISECOND, TASK_FOREVER, &task_odometry_ros, &ts, true);


void setup() { 
  pinMode(LED,OUTPUT);
  i2c.setClock(400000);
  i2c.begin();
  i2c_sonar.begin();
  nh.initNode();
  init_ina_current_sens(&i2c, &nh);
  init_mpu_imu_ros(&i2c, &nh);
  init_sonar_ros(&i2c_sonar, &nh);
  init_optical_ros(&nh);
  init_drive_ros(&nh);
  
}

void loop() {
  ts.execute();
}