
/*
 signal to pin with S (left)
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(36, INPUT);
}

void loop() {
 digitalWrite(0, HIGH); 
 digitalWrite(2, HIGH);
 int foto = digitalRead(36);
 if(foto == HIGH) Serial.println("Wysoki");
 else Serial.println("Niski");
  delay(1000);
  digitalWrite(0, LOW); 
  digitalWrite(2, LOW);
  delay(1000); 
\
}
