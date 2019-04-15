//NIE DZIAŁA ZEWNĘTRZNE ZASILANIE!

void setup() {
  Serial.begin(115200);

}

void loop() {
 float level = analogRead(A13);
 Serial.println(level);
 delay(1000);
}
