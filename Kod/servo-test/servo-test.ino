//NodeMCU-32s nie działa!
#include <ESP32Servo.h>
Servo servo;

//const float PI = 3.1415;
void setup() {
  servo.attach(15);
  Serial.begin(115200);
}

void loop() {
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}
