#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

int silnikA1 = 5; 
int silnikA2 = 6;
int silnikB1 = 8;
int silnikB2 = 7;

int stan = 'g'; 

void mkStop(){
digitalWrite(silnikA1, LOW);
digitalWrite(silnikA2, LOW);
digitalWrite(silnikB2, LOW);
digitalWrite(silnikB1, LOW);
delay(5);
}

void setup() {
Serial.begin(9600);
pinMode(silnikA1, OUTPUT);
pinMode(silnikA2, OUTPUT);
pinMode(silnikB1, OUTPUT);
pinMode(silnikB2, OUTPUT);
 mySerial.begin(9600l);
}

void loop() {
if (mySerial.available()){
  stan = mySerial.read();
    Serial.write(stan);
}
 
    
if(Serial.available()>0){ // lee el bluetooth y almacena en stan
stan = Serial.read();
}
if(stan=='a'){ //forward
  mkStop();
digitalWrite(silnikA1, LOW);
digitalWrite(silnikA2, HIGH);
digitalWrite(silnikB2,HIGH);
digitalWrite(silnikB1, LOW);
}
if(stan=='b'){ // left
  mkStop();
digitalWrite(silnikA1, HIGH);
digitalWrite(silnikA2, LOW);
digitalWrite(silnikB2, HIGH);
digitalWrite(silnikB1, LOW);
}
if(stan=='d'){ // right
  mkStop();
digitalWrite(silnikA1, LOW);
digitalWrite(silnikA2, HIGH);
digitalWrite(silnikB2, LOW);
digitalWrite(silnikB1, HIGH);
}
if(stan=='e'){ // backward
  mkStop();
digitalWrite(silnikA1, HIGH);
digitalWrite(silnikA2, LOW);
digitalWrite(silnikB1, HIGH);
digitalWrite(silnikB2, LOW);
}

if(stan=='c'){ //stop
mkStop();
}
if (stan =='f'){ 

}
if (stan=='g'){
  digitalWrite(silnikA1, LOW);
digitalWrite(silnikA2, LOW);
digitalWrite(silnikB2, LOW);
digitalWrite(silnikB1, LOW);
}
delay(10);
}
