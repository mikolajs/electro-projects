
void setup() {
  for(int i = 0; i <= 5; i++) pinMode(i, OUTPUT);
  for(int i = 12; i <= 16; i++) pinMode(i, OUTPUT);

}

void loop() {

  for(int i = 0; i <= 5; i++) digitalWrite(i, HIGH);
  for(int i = 12; i <= 16; i++) digitalWrite(i, HIGH);
  delay(2000);
  for(int i = 0; i <= 5; i++) digitalWrite(i, LOW);
  for(int i = 12; i <= 16; i++) digitalWrite(i, LOW);
  delay(2000);

}
