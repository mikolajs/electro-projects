#include <Ultrasonic.h>

int trig = 16;
int echo = 5;
int power = 14;
int led = 19;

int n = 0;
Ultrasonic ultrasonic(trig, echo, 40000UL);

void setup() {
  pinMode(led, OUTPUT);
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);
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
  Serial.println(dist);
  delay(1000);
}
