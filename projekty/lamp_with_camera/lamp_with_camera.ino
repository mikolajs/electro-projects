#define LED_FLASH_PIN 4
#define LIGTH_SENSOR 12

void setup() {
  Serial.begin(115200);
  pinMode(LED_FLASH_PIN, OUTPUT);
  pinMode(LIGTH_SENSOR, INPUT);
}

void loop() {
  int lightVal = analogRead(LIGTH_SENSOR);
  Serial.println(lightVal);
  if(lightVal > 200)
    digitalWrite(LED_FLASH_PIN, HIGH); 
  else 
    digitalWrite(LED_FLASH_PIN, LOW); 
  delay(2000);
}
