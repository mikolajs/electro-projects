void setup() {
  analogWriteFreq(18000);
  pinMode(2, OUTPUT);
}

void loop() {
  analogWrite(2, 0);
  delay(5000);
  analogWrite(2, 255);
  delay(5000);
}
