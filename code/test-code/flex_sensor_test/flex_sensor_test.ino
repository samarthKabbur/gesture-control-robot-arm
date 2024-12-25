/******************************************************************************
  Author: Smartbuilds.io
  YouTube: https://www.youtube.com/channel/UCGxwyXJWEarxh2XWqvygiIg
  Fork your own version: https://github.com/EbenKouao/arduino-robotic-arm
  Date: 28/12/2020
  Description: Test the Flex Sensor
******************************************************************************/
const int flexPin = A3; // Pin connected to voltage divider output
int time;
int newTime;
int avgRead;
int count;
bool timeFlag;

#define THRESHOLD 140
void setup()
{
  Serial.begin(4800);
  pinMode(flexPin, INPUT);


  timeFlag = true;
  avgRead = 0;
  count = 0;
}

void loop()
{
  if (timeFlag == true){
    time = millis();
    newTime = millis();
    timeFlag = false;
  }
 
  // Read the ADC, and calculate voltage and resistance from it
  int flexSensor = analogRead(flexPin);
  avgRead += flexSensor;
  count += 1;
  newTime = millis();

  if (newTime - time >= 1000){
    avgRead /= count;
    // Serial.println(avgRead);
    timeFlag = true;
    count = 0;
    if (avgRead < THRESHOLD){
      Serial.println("Finger Flexed");
    } else {
      Serial.println("Finger Straight");
    }
  }
  delay(50);
}
