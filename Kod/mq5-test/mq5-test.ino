/*Podłączyć na 3,3V, bo się grzeje. 
analogRead czyta na 4096 12-bit?
*/
int valueAnalog = 0;
int valueMap = 0;
int analogPin = 0; 

void setup() {
  Serial.begin(115200);
  
}

void loop() {
  valueAnalog = analogRead(analogPin);
  valueMap = map(valueAnalog, 0, 4096, 0, 100);
  String info = "MQ5, maped read: " + String(valueMap) + " analog " + String(valueAnalog);
  if(valueMap > 20){
    Serial.print(info);
    Serial.println(" Wykryto gaz lub CO");
  } else {
    Serial.println(info);
  }
  delay(4000);
}
