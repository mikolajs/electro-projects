#include <Ultrasonic.h>

int t = 12;
int e = 13;
int b = 4;

Ultrasonic ultrasonic(t, e, 40000UL);

void setup() {
  Serial.begin(9600);
  pinMode(b, OUTPUT);
}

void pikanie(int dystans){
  int p = 10 - map(dystans, 0, 250, 0, 9);
  int czas = 1000 / p;
  for(int i = 0; i < p; i++){
    tone(b, 440, 100);
    delay(czas);
  }
}

void loop() {
  int dystans = ultrasonic.read();
  pikanie(dystans);
  Serial.println(dystans);
  delay(1);
}
