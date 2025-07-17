//od lewej (bez metalu strona) +, -, PIN15, zasilanie 3.3V, do lewego, od tamtąd do + LED, od LED do GND (-)

void setup() {
  // put your setup code here, to run once:
  pinMode(15, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(15, HIGH);
  delay(2000);
  digitalWrite(15, LOW);
  delay(2000);
}
