#include "flex_sensor.h"

const int thumbPin = A1;
const int pointerPin = A2;
const int middlePin = A3;

Flex_Sensor thumb;
Flex_Sensor pointer;
Flex_Sensor middle;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);

  thumb.initialize();
  thumb.setThreshold(100);
  thumb.set_flexPin(thumbPin);

  pointer.initialize();
  pointer.setThreshold(100);
  pointer.set_flexPin(pointerPin);

  middle.initialize();
  middle.setThreshold(100);
  middle.set_flexPin(middlePin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (thumb.isBent()){
    Serial.println("Thumb bent");
  }
  if (pointer.isBent()){
    Serial.println("pointer bent");
  }
  // if (middle.isBent()){
  //   Serial.println("middle bent");
  // }


  delay(50);
}
