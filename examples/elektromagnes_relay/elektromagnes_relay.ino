//Potrzebny mocniejsze zasilanie 5V to ledwo działa. 
//Przekaźnik Relay, też musi być dla mniejszych napięć nie dla ~230V
int PIN = 23;

void setup() {
  Serial.begin(112500);
  pinMode(PIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN, HIGH);
  delay(5000);
  digitalWrite(PIN, LOW);
  delay(5000);

}
