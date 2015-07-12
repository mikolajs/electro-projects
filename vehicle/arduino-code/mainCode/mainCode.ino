#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX
char character;
int p= 0;
void setup()  
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() // run over and over
{
  //String Data = "";
  //Serial.print(mySerial.read());
  
  if(mySerial.available()){
    character = mySerial.read();
    p= 50;
  }
  
  switch(character) {
  case 'a':
    analogWrite(9, 0);
    analogWrite(10, p);
    analogWrite(5, 0);
    analogWrite(6, p);
    break;
  case 'e':
    analogWrite(9, p);
    analogWrite(10, 0);
    analogWrite(5, p);
    analogWrite(6, 0);
    break;
  case 'd':
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(5, 0);
    analogWrite(6, p);
    break;
  case 'b':
    analogWrite(9, 0);
    analogWrite(10, p);
    analogWrite(5, 0);
    analogWrite(6, 0);
    break;
  case 'c':
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
    p = 0;
    break;
    default:
    break;
  }
  delay(50);
  if(p < 250) p+= 10;
  

}

