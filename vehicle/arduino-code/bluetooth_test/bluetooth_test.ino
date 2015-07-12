#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); // RX, TX
char character;
int count = 0;
void setup()  
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() // run over and over
{
    //String Data = "";
    //Serial.print(mySerial.read());
    if(mySerial.available()){
      character = mySerial.read();
      Serial.println(character);
       switch(character) {
         case 'a':
         digitalWrite(9,0);
         digitalWrite(10,1);
         digitalWrite(11,0);
         digitalWrite(12,1);
         break;
          case 'e':
         digitalWrite(9,1);
         digitalWrite(10,0);
         digitalWrite(11,1);
         digitalWrite(12,0);
         break;
          case 'd':
         digitalWrite(9,0);
         digitalWrite(10,0);
         digitalWrite(11,0);
         digitalWrite(12,1);
         break;
          case 'b':
         digitalWrite(9,0);
         digitalWrite(10,1);
         digitalWrite(11,0);
         digitalWrite(12,0);
         break;
         case 'c':
         digitalWrite(9,0);
         digitalWrite(10,0);
         digitalWrite(11,0);
         digitalWrite(12,0);
         break;
         default:
         break;
     }
    } else
    {
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
      digitalWrite(12,0);
    }
     
     delay(50);
     
}
