/*
* relay: środkow dziurka wejście. Środkowa wyście. Przy innym
* podłączeniu działa przy HIGH jako wyłączony
* RELAY ma tendencję do niewyłączania się dla małych prądów
*/
void switchOFF();
const int POWER = 4; //D5

void setup() {
  pinMode(POWER, OUTPUT);
}
void loop() {
  digitalWrite(POWER, HIGH); //ON
  delay(1000);
  digitalWrite(POWER, LOW); //FF
  delay(4000); 

}

void switchOFF(){
 digitalWrite(POWER, LOW); //FF
  delay(200);
 digitalWrite(POWER, HIGH); //ON
  delay(200);
  digitalWrite(POWER, LOW); //FF
 delay(200);
}
