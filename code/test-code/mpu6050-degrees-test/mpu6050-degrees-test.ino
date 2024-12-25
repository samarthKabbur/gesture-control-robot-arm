/******************************************************************************
  Author: Smartbuilds.io
  YouTube: https://www.youtube.com/channel/UCGxwyXJWEarxh2XWqvygiIg
  Fork your own version: https://github.com/EbenKouao/arduino-robotic-arm
  Date: 28/12/2020
  Description: Test the MPU relative position X & Y co-ord in degreed

******************************************************************************/

#include<Wire.h>

#define button 8
int state = 0;
int buttonState = 0;
int check = 1;
int nil = 0;

const int MPU2 = 0x69, MPU1 = 0x68;

int16_t AcX1, AcY1, AcZ1, Tmp1, GyX1, GyY1, GyZ1;

int minVal = 0;
int maxVal = 365;

// double x1;
// double y1;
// double z1;

// double x2;
// double y2;
// double z2;

double x, y, z;

int response_time = 40;

void setup() {
  pinMode(3, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);// PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);// PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(19200);
  delay(1000);
  // x1 = 0;
  // y1 = 0;
  // z1 = 0;
  // x2 = 0;
  // y2 = 0;
  // z2 = 0;

}
void loop() {
  //get values for first mpu having address of 0x68
  /*x1, y1, z1 = */ GetMpuValue1(MPU1/*, x1, y1, z1*/);
  Serial.print("/");
  /*x2, y2, z2 = */ GetMpuValue1(MPU2/*, x2, y2, z2*/);
  Serial.println();
  delay(50);
}
                               /*, double x, double y, double z*/
void GetMpuValue1(const int MPU) {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers and place in the i2c access buffer

  AcX1 = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY1 = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ1 = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Tmp needs to be read because of how data is strctured in the i2c access buffer
  Tmp1 = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  int xAng = map(AcX1, minVal, maxVal, -90, 90);
  int yAng = map(AcY1, minVal, maxVal, -90, 90);
  int zAng = map(AcZ1, minVal, maxVal, -90, 90);

  GyX1 = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY1 = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ1 = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI) + 4; //offset by 4 degrees to get back to zero
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  // x += AcX1;
  // y += AcY1;
  // z += AcZ1;


  //Serial.print("AngleX= ");
  Serial.print(x);
  Serial.print("/");
  //Serial.print("\t");

  //Serial.print("AngleY= ");
  Serial.print(y);
  Serial.print("/");
  //Serial.print("\t");

  //Serial.print("AngleZ= ");
  Serial.print(z); 
  //Serial.print("\t");
  //Serial.println("-----------------------------------------");

  // return x, y, z;
}
