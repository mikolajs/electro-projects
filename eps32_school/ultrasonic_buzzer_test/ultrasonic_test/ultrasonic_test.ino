#include <Ultrasonic.h>

int trig = 0;
int echo = 1;

int led = 3;
int buzzer = 2;

int n = 0;
Ultrasonic ultrasonic(trig, echo, 40000UL);

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
}

void light(bool on) {
  if(on) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}

void loop() {
  Serial.print("Start LOOP");
  Serial.println(" ");
  unsigned int dist = ultrasonic.read();
  if(dist < 100) light(true);
  else light(false);
  tone(buzzer, 100); ///prosty ma i tak tylko jeden ton
  Serial.println(dist);
  delay(1000);
}
