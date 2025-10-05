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

void setup() {
  Serial.begin(112000); 
  pinMode(POWER, OUTPUT);
  Serial.println("Dallas Temperature IC Control Library Demo"); 
  sensors.begin(); 
}
void loop() {
  Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); 
  Serial.println("DONE"); 
  Serial.print("Temperature is: "); 
  Serial.print(sensors.getTempCByIndex(0));
  digitalWrite(POWER, HIGH); //ON
  delay(1000);
  digitalWrite(POWER, LOW); //FF
  delay(3000); 

}

void switchOFF(){
 digitalWrite(POWER, LOW); //FF
  delay(200);
 digitalWrite(POWER, HIGH); //ON
  delay(200);
  digitalWrite(POWER, LOW); //FF
 delay(200);
}
