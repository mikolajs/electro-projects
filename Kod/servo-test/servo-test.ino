//uszkodzę silnik jeśli dam pozycję powyżej 180!!!!
//niebieski jest kiepski jakościowo
//#include <ESP32Servo.h>
#include <Servo.h>
Servo servo;

//const float PI = 3.1415;
void setup() {
  servo.attach(15);  Serial.begin(115200);
  servo.write(0);
  delay(2000);
}

void loop() {
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(30);
  }

  for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(30);
  }
}
