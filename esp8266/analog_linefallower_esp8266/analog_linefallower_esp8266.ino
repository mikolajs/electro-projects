int lev = 0;

void setup() {
 Serial.begin(115200);
}

void loop() {
  lev = analogRead(A0);
  Serial.println(lev);
  delay(200);
}
