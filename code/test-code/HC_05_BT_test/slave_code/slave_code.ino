#define ledPin 9

int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    state = Serial.read();
  }
  if (state == '1'){
    digitalWrite(ledPin, HIGH);
  } else if (state == '0'){
    digitalWrite(ledPin, LOW);
  }
}
