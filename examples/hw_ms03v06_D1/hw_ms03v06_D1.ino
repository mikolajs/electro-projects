//D1 mini
//https://github.com/cyrixninja/LD2420
#include "LD2420.h"
#include <SoftwareSerial.h>
#define LED  2
SoftwareSerial sensorSerial(4, 5); // RX, TX
LD2420 radar;
void setup() {
  Serial.begin(115200);
  sensorSerial.begin(115200);
  pinMode(LED, OUTPUT);
  if (radar.begin(sensorSerial)) {
    Serial.println("Radar initialized!");
    radar.onDetection(onObjectDetected);
  }
  
}

void loop() {
  radar.update();
  delay(10);
  // digitalWrite(LED, HIGH);
  // delay(10);
  // digitalWrite(LED, LOW);

}

void onObjectDetected(int distance) {
  Serial.print("Object at ");
  Serial.print(distance);
  Serial.println(" cm");
}
