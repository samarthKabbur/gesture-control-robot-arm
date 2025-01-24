/******************************************************************************
  Author: Smartbuilds.io
  YouTube: https://www.youtube.com/channel/UCGxwyXJWEarxh2XWqvygiIg
  Fork your own version: https://github.com/EbenKouao/arduino-robotic-arm
  Date: 28/12/2020
  Description: Test the Stepper Motor
******************************************************************************/

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;
int stepDelay = 9500;
void setup()
{
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  baseRotateLeft();
  baseRotateRight();
  Serial.println("motor moving");
}

void baseRotateLeft() {
  //clockwise
  digitalWrite(dirPin, HIGH);
  // Spin motor
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  delay(2000); // Wait a second
}


void baseRotateRight() {

  //counterclockwise
  digitalWrite(dirPin, LOW);
  // Spin motor
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
  }
  delay(2000); // Wait a second
}
