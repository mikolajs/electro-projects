/*
* relay: środkow dziurka wejście. Środkowa wyście. Przy innym
* podłączeniu działa przy HIGH jako wyłączony
* RELAY ma tendencję do niewyłączania się dla małych prądów
*/
#include <OneWire.h> 
#include <DallasTemperature.h>
void switchOFF();
const int POWER = 4; //D1

#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
const int BUZZER_PIN = 14;

const float expectedTemp1 = 63.5;
const float expectedTemp2 = 71.0;
bool started = false;
int toEnd1 = 2100000;
int toEnd2 = 1800000;
float T = 0;
const int delta = 5000;

void setup() {
  Serial.begin(112000); 
  pinMode(POWER, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
  Serial.println("Dallas Temperature IC Control Library Demo"); 
  sensors.begin(); 
}
void loop() {
  //inform();
  sensors.requestTemperatures(); 
  T = sensors.getTempCByIndex(0);
  digitalWrite(BUZZER_PIN, HIGH);
  Serial.print("Temperature is: "); 
  Serial.println(T);
  digitalWrite(BUZZER_PIN, HIGH);
  if(!started) firstWarming();
  else if(toEnd1 > 0) warming1();
  else if(toEnd2 > 0) warming2();
  else inform();
  digitalWrite(BUZZER_PIN, HIGH);
  delay(delta); 
}

void firstWarming(){
  Serial.println("first Warming");
  if(T < expectedTemp1) digitalWrite(POWER, HIGH);
  else started = true;
}

void warming1(){
  toEnd1 -= delta;
  Serial.println("warming etap 1");
  if(T <= expectedTemp1) digitalWrite(POWER, HIGH);
  else digitalWrite(POWER, LOW);
}

void warming2(){
  toEnd2 -= delta;
  Serial.println("warming etap 2");
  if(T <= expectedTemp2) digitalWrite(POWER, HIGH);
  else digitalWrite(POWER, LOW);
}

void inform(){
  for(int i = 0; i < 5; i++){
  digitalWrite(BUZZER_PIN, LOW);
  delay(600);
  analogWrite(BUZZER_PIN, HIGH);
  delay(600);
  } 
}

