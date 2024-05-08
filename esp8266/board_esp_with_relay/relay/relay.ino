/*
* relay: środkow dziurka wejście. Środkowa wyście. Przy innym
* podłączeniu działa przy HIGH jako wyłączony
* RELAY ma tendencję do niewyłączania się dla małych prądów
*/
void switchOFF();
const int POWER = 4; 

void setup() {
  pinMode(POWER, OUTPUT);
  pinMode(16, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  Serial.println("Działa");
  digitalWrite(POWER, HIGH); //ON
  digitalWrite(16, HIGH);
  delay(1000);
  digitalWrite(POWER, LOW); //FF
  digitalWrite(16, LOW);
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
