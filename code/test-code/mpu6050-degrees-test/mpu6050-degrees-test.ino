/******************************************************************************
  Author: Smartbuilds.io
  YouTube: https://www.youtube.com/channel/UCGxwyXJWEarxh2XWqvygiIg
  Fork your own version: https://github.com/EbenKouao/arduino-robotic-arm
  Date: 28/12/2020
  Description: Test the MPU relative position X & Y coordinates in degrees
******************************************************************************/

#include <Wire.h> // Include the Wire library for I2C communication

#define button 8 // Define the button pin

// Initialize variables for button and system state
int state = 0;
int buttonState = 0;
int check = 1;
int nil = 0;

// Define MPU addresses
const int MPU2 = 0x69, MPU1 = 0x68;

// Variables to store accelerometer, temperature, and gyroscope data
int16_t AcX1, AcY1, AcZ1, Tmp1, GyX1, GyY1, GyZ1;

int minVal = 0; // Minimum value for sensor calibration
int maxVal = 365; // Maximum value for sensor calibration
double x, y, z; // Variables to store calculated angles

int response_time = 40; // Response time for the loop delay

void setup() {
  pinMode(3, OUTPUT); // Set pin 3 as an output
  
  Wire.begin(); // Initialize the I2C communication

  // Wake up MPU1
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B); // Write to the PWR_MGMT_1 register
  Wire.write(0); // Set to zero to wake up the MPU-6050
  Wire.endTransmission(true);

  // Wake up MPU2
  Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B); // Write to the PWR_MGMT_1 register
  Wire.write(0); // Set to zero to wake up the MPU-6050
  Wire.endTransmission(true);

  Serial.begin(19200); // Begin serial communication at 19200 baud
  delay(1000); // Delay for stabilization
}

void loop() {
  // Get values from the first MPU (address 0x68)
  GetMpuValue1(MPU1);
  Serial.print("/");

  // Get values from the second MPU (address 0x69)
  GetMpuValue1(MPU2);
  Serial.println(); // Print a newline
  delay(50); // Wait 50ms before the next loop iteration
}

// Function to retrieve MPU data and calculate angles
void GetMpuValue1(const int MPU) {
  Wire.beginTransmission(MPU); // Start communication with the MPU
  Wire.write(0x3B); // Start reading at register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // Request 14 registers (accelerometer, temp, and gyroscope data)

  // Read accelerometer data
  AcX1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for ACCEL_XOUT
  AcY1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for ACCEL_YOUT
  AcZ1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for ACCEL_ZOUT

  // Read temperature data (must be read to continue to gyro data)
  Tmp1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for TEMP_OUT

  // Map accelerometer data to angle ranges
  int xAng = map(AcX1, minVal, maxVal, -90, 90);
  int yAng = map(AcY1, minVal, maxVal, -90, 90);
  int zAng = map(AcZ1, minVal, maxVal, -90, 90);

  // Read gyroscope data
  GyX1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for GYRO_XOUT
  GyY1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for GYRO_YOUT
  GyZ1 = Wire.read() << 8 | Wire.read(); // Combine high and low bytes for GYRO_ZOUT

  // Calculate angles using accelerometer data
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI) + 4; // Offset by 4 degrees to calibrate
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  // Print calculated angles
  Serial.print(x);
  Serial.print("/");
  Serial.print(y);
  Serial.print("/");
  Serial.print(z);
}