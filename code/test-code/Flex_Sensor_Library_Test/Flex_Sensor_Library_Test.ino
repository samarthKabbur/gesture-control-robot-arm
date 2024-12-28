#include "flex_sensor.h"

const int flexPin = A1;

Flex_Sensor thumb;
Flex_Sensor pointer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  thumb.initialize();
  thumb.setThreshold(100);
  thumb.set_flexPin(flexPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Thumb: ")
  thumb.printFingerState();
  delay(50);
}
