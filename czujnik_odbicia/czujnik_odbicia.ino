int s = 4;

void setup() {
  pinMode(s, INPUT);
  Serial.begin(9600);
}

void loop() {
  float level = analogRead(A1);
    Serial.println(level);
    delay(200);

}
