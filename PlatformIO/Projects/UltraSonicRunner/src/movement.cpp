#include "movement.h"
#include <Arduino.h>


Motors::Motors(int a1, int a2, int b1, int b2){
    A_1 = a1;
    A_2 = a2;
    B_1 = b1;
    B_2 = b2;
};

void Motors::forward(){
    digitalWrite(A_1, HIGH);
    digitalWrite(A_2, LOW);
    digitalWrite(B_1, HIGH);
    digitalWrite(B_2, LOW);
};

void Motors::backward(){
    digitalWrite(A_1, LOW);
    digitalWrite(A_2, HIGH);
    digitalWrite(B_1, LOW);
    digitalWrite(B_2, HIGH);
};

void Motors::stop(){
    digitalWrite(A_1, LOW);
    digitalWrite(A_2, LOW);
    digitalWrite(B_1, LOW);
    digitalWrite(B_2, LOW);
};

void Motors::left(){
    digitalWrite(A_1, HIGH);
    digitalWrite(A_2, LOW);
    digitalWrite(B_1, LOW);
    digitalWrite(B_2, HIGH);
};

void Motors::right(){
    digitalWrite(A_1, LOW);
    digitalWrite(A_2, HIGH);
    digitalWrite(B_1, HIGH);
    digitalWrite(B_2, LOW);
};