/**
 * Podłączamy miernik szeregowo, jest on amperomierzem. 
 * Jeśli chcemy z niego zrobić woltomierz to podłączamy
 * szeregowo opornik (w przykładzie 1000
 */
int analogPin = A0;
int val = 0;
int sensitivity = 100;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
int resistorOmh = 250;

void setup() {
 Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);
  adcVoltage = (val / 1024.0)*5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  Serial.print(currentValue*resistorOmh);
  Serial.println(" V");
  Serial.println(currentValue);
  Serial.println(" A");
  delay(500);
}
