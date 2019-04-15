#include <ESP32Servo.h>


Servo servo1;

void setup() {
  servo1.attach(27);
}
void loop() {
  servo1.write(-360);
  delay(100);
//  int pos;
//   for (pos = 180; pos >= 0; pos -= 1) { // sweep from 180 degrees to 0 degrees
//      servo1.write(pos);
//      delay(20);
//    }
//
//    for (pos = 0; pos <= 180; pos += 1) { // sweep from 0 degrees to 180 degrees
//      // in steps of 1 degree
//      servo1.write(pos);
//      delay(20);                       // waits 20ms for the servo to reach the position
//  }

}
