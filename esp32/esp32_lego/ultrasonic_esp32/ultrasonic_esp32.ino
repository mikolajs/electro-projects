#include <Ultrasonic.h>

int trig = 2;
int echo = 5;
int led = 0;

Ultrasonic ultrasonic(trig, echo, 40000UL);

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);

}

void light(bool on) {
  if(on) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}

void loop() {
  Serial.print("Time ");
  Serial.print(millis());
  int dist = ultrasonic.read();
  if(dist < 100) light(true);
  else light(false);
  Serial.print(" distance: ");
  Serial.println(dist);
  delay(1000);
}
