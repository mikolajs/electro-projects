//potencjometr center Analog right +, left - min 182??? trudno ustalić, max 1024
//użyć w środkowym pinie opornik aby nie przekroczyło 1V, 100Ω i 220Ω (eps8266 i esp32 ??)
//ESP8266 pins
//int A = 16; //ESP32?
//Minimum
int LED = 5;
int val = 0;
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  val = analogRead(A0);
  Serial.print("potentiometer=");
  Serial.println(val);
  if(val > 400) {
    digitalWrite(LED, HIGH);
  } else digitalWrite(LED, LOW);
  delay(2000);
}
