#include "Arduino.h"
//dla duzego stepera
//podłaczamy na przemian 16 i 18 do Motor A, 17, 19 do Motor B
//const int STEP_1 = 16;
//const int STEP_2 = 17;
//const int STEP_3 = 18;
//const int STEP_4 = 19;
const int STEP_1 = 5;
const int STEP_2 = 4;
const int STEP_3 = 0;
const int STEP_4 = 2;


const int WAIT = 2;

void setup(){
	pinMode(STEP_1, OUTPUT);
	pinMode(STEP_2, OUTPUT);
	pinMode(STEP_3, OUTPUT);
	pinMode(STEP_4, OUTPUT);
}

void step(){
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

void loop(){
    step();
}


