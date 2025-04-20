//NodeMCU-32s nie działa!
#include <ESP32Servo.h>
Servo servo;

int pos = 0;

void setup() {
  servo.attach(5);
  Serial.begin(115200);
}

void loop() {
  for(pos = 0; pos <= 180; pos++){
    servo.write(pos);
    delay(10);
  }
  for(pos = 180; pos >= 0; pos--){
    servo.write(pos);
    delay(10);
  }
  Serial.println("next");
  delay(100);
}
