#include "flex_sensor.h"
#include <SoftwareSerial.h>

#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial mySerial(RX_PIN, TX_PIN);

const int flexPin = A1;

Flex_Sensor flex;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  mySerial.begin(38400);
  flex.initialize();
  flex.setThreshold(100);
  flex.set_flexPin(flexPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(1000);
  // Serial.write('1');
  // delay(1000);
  // Serial.write('0');
  if (flex.isBent()){
    mySerial.write('1');
    Serial.println("Sending bent");
  } else {
    mySerial.write('0');
  }

  delay(50);
}
