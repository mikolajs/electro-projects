/*
Nie działa!
bąz  -, czerwień +, pomarańcz sygnał
*/
#include <ESP32Servo.h>

int led = 13;
Servo myServo;

void setup() {
  pinMode(led, OUTPUT);
  myServo.attach(0);
  myServo.write(0);
}

void light(bool on) {
  if(on) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}

void loop() {
  light(true);
  myServo.write(0);
  for(int posDegrees = 0; posDegrees <= 90; posDegrees++) {
    myServo.write(posDegrees);
    delay(20);
  }
  light(false);
  for(int posDegrees = 90; posDegrees >= 0; posDegrees--) {
    myServo.write(posDegrees);
    delay(20);
  }
}