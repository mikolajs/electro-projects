int sig = 22;
int led = 2;

void setup() {
  pinMode(sig, INPUT);
  Serial.begin(115200);
}

void loop() {
   Serial.print("Time ");
  Serial.print(millis());
  int dist = digitalRead(sig);
  if(dist == 1) digitalWrite(sig, HIGH);
  else digitalWrite(sig, LOW);
  Serial.print(" distance: ");
  Serial.println(dist);
  delay(1000);

}
