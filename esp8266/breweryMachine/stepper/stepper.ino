//#include <Servo.h>
#include <ESP8266WiFi.h>


const int STEP_1 = 5; //D1 – A-1A
const int STEP_2 = 4; //D2 – B-1A
const int STEP_3 = 0; //D3 – A-1B
const int STEP_4 = 2; //D4 – B-2A

int move = -1; // -1 down 1 up 0 stop

const int WAIT = 10;


long lastCommand = 0;
long currentTime;
long previousTime;
long timeoutTime = 2000;
String header;

void setup(){
  pinMode(STEP_1, OUTPUT);
  pinMode(STEP_2, OUTPUT);
  pinMode(STEP_3, OUTPUT);
  pinMode(STEP_4, OUTPUT);
   Serial.begin(115200);
}

void stepDown(){
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, HIGH);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, HIGH);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, HIGH);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, HIGH);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
}

void stepUp(){
  digitalWrite(STEP_1, HIGH);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, HIGH);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, HIGH);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, HIGH);
  delay(WAIT);
}

void mkMove(){
  switch(move){
    case -1: 
      stepUp();
      break;
    case 1: 
      stepDown();
      break;
    default:
      break;
  }
}


void loop() {
      mkMove();
}
