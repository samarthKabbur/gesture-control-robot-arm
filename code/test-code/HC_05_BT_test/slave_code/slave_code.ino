#define ledPin 9
#include <SoftwareSerial.h>

#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial mySerial(RX_PIN, TX_PIN);

int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(38400);
  mySerial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available() > 0){
    state = mySerial.read();
    Serial.println(state);
  }
  if (state == '1'){
    digitalWrite(ledPin, HIGH);
  } else if (state == '0'){
    digitalWrite(ledPin, LOW);
  }
}
