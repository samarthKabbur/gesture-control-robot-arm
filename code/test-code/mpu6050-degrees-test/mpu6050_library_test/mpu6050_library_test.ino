#include "GY521.h"
#include <Wire.h>

GY521 gy521;

void setup() {
  // put your setup code here, to run once:
  gy521.initialize(MPU6050_I2C_ADDRESS_1);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  SensorData_t data;
  data = returnEverything(MPU6050_I2C_ADDRESS_1);
  Serial.print(data.filtered_angles.x);
  Serial.print("/");
  Serial.print(data.filtered_angles.y);
  Serial.print("/")
  Serial.println(data.filtered_angles.z);
}
