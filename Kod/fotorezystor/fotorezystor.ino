int a = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  a = analogRead(A5);
  Serial.println(a);
  delay(100);
}
