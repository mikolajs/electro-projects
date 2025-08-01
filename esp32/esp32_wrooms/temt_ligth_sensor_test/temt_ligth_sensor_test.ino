#define LED 0
#define LIGHT 13 //only left side pins can analog read
int lightVal = 0; 

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LIGHT, INPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  lightVal = analogRead(LIGHT); ///0-4095 default
  Serial.println(lightVal);
  if(lightVal < 20) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
  delay(4000);
}
