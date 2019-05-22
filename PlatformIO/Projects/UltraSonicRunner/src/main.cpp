#include <Arduino.h>
#include <Ultrasonic.h>
#include "movement.h"

#define left_motor_A 3
#define left_motor_B 4
#define right_motor_A 5
#define right_motor_B 6
#define ultrasonic_t 11
#define ultrasonic_e 12

const int TONEAR = 10;

Motors m(left_motor_A,left_motor_B,right_motor_A,right_motor_B);
Ultrasonic us(ultrasonic_t, ultrasonic_e);

void setup() {
  pinMode(left_motor_A, INPUT);
  pinMode(left_motor_B, INPUT);
  pinMode(right_motor_A, INPUT);
  pinMode(right_motor_B, INPUT);
  randomSeed(time(NULL));
}

void loop() {
  int dist = us.read();
  if(dist < TONEAR){
    m.stop();
    delay(1);
    if(rand() % 2 == 0){
      m.left();
    } else {
      m.right();
    }
    delay(200);
    m.stop();
  } 
  m.forward();
  delay(500);
}