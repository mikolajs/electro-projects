int pins[] = {16, 17, 26, 27, 23};
const int P = 5;
void setup() {
  Serial.begin(115200);
  for(int p = 0; p < P; p++) pinMode(pins[p], OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < P; i++) digitalWrite(pins[i], HIGH);

  delay(2000);
  for(int i = 0; i < P; i++) digitalWrite(pins[i], LOW);
  delay(2000);
}
