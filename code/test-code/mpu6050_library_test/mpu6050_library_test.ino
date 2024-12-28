#include "GY521.h"
#include <Wire.h>

GY521 gy521;

const int MPU_ADDR_1 = 0x68;

void setup() {
  // put your setup code here, to run once:
  gy521.initialize();
  Serial.begin(19200);
  gy521.set_mpu_addr(MPU_ADDR_1);
}

void loop() {
  // put your main code here, to run repeatedly:
  SensorData_t data;
  data = gy521.returnMPUData();
  Serial.print(data.filtered_angles.x);
  Serial.print("/");
  Serial.print(data.filtered_angles.y);
  Serial.print("/");
  Serial.println(data.filtered_angles.z);
}
