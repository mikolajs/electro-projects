#include <NewPing.h>

int silnik1A = 5;
int silnik1B = 6;
int silnik2A = 9;
int silnik2B = 10;

 NewPing sonar(11, 12, 200);
 
void setup() {
  pinMode(silnik1A, OUTPUT);
  pinMode(silnik1B, OUTPUT);
  pinMode(silnik2A, OUTPUT);
  pinMode(silnik2B, OUTPUT);
  Serial.begin(9600);
}

void przod(){
  digitalWrite(silnik1A, HIGH);
  digitalWrite(silnik1B, LOW);
  digitalWrite(silnik2A, HIGH);
  digitalWrite(silnik2B, LOW);
}

void tyl(){
  digitalWrite(silnik1A, LOW);
  digitalWrite(silnik1B, HIGH);
  digitalWrite(silnik2A, LOW);
  digitalWrite(silnik2B, HIGH);
}

void prawo(){
  digitalWrite(silnik1A, LOW);
  digitalWrite(silnik1B, HIGH);
  digitalWrite(silnik2A, HIGH);
  digitalWrite(silnik2B, LOW);
}

void lewo(){
  digitalWrite(silnik1A, HIGH);
  digitalWrite(silnik1B, LOW);
  digitalWrite(silnik2A, LOW);
  digitalWrite(silnik2B, HIGH);
}

void loop() {
  przod();
  delay(100);
 unsigned int odleglosc = sonar.ping_cm();
 if(odlegosc < 20) {
  tyl();
  delay(100);
  prawo();
  delay(500);
 }
 }
 
 delay(1000);
}
