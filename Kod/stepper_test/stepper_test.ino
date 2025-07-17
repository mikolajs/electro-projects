//#include "Arduino.h"
//dla duzego stepera 
//niezbędne zasilanie 5V lub 12V. ???
//podłaczamy na przemian 16 i 18 do Motor A, 17, 19 do Motor B
// const int STEP_1 = 26;
// const int STEP_2 = 27;
// const int STEP_3 = 14;
// const int STEP_4 = 12;
// const int STEP_1 = 5;
// const int STEP_2 = 4;
// const int STEP_3 = 0;
// const int STEP_4 = 2;


// const int WAIT = 10;

// void setup(){
// 	pinMode(STEP_1, OUTPUT);
// 	pinMode(STEP_2, OUTPUT);
// 	pinMode(STEP_3, OUTPUT);
// 	pinMode(STEP_4, OUTPUT);
//   Serial.begin(115200);
// }

// void step(){
// 	digitalWrite(STEP_1, HIGH);
// 	digitalWrite(STEP_2, LOW);
// 	digitalWrite(STEP_3, LOW);
// 	digitalWrite(STEP_4, LOW);
// 	delay(WAIT);
// 	digitalWrite(STEP_1, LOW);
// 	digitalWrite(STEP_2, HIGH);
// 	digitalWrite(STEP_3, LOW);
// 	digitalWrite(STEP_4, LOW);
// 	delay(WAIT);
// 	digitalWrite(STEP_1, LOW);
// 	digitalWrite(STEP_2, LOW);
// 	digitalWrite(STEP_3, HIGH);
// 	digitalWrite(STEP_4, LOW);
// 	delay(WAIT);
// 	digitalWrite(STEP_1, LOW);
// 	digitalWrite(STEP_2, LOW);
// 	digitalWrite(STEP_3, LOW);
// 	digitalWrite(STEP_4, HIGH);
// 	delay(WAIT);
// }

// void loop(){
//     Serial.println("Next step");
//     step();
// }
#include <Stepper.h>

const int stepsPerRevolution = 1024;  // change this to fit the number of steps per revolution //nie zadziała na 2048 napięcie?

// ULN2003 Motor Driver Pins
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void setup() {
  // set the speed at 5 rpm
  myStepper.setSpeed(15);
  // initialize the serial port
  Serial.begin(115200);
}

void loop() {
  // step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}


