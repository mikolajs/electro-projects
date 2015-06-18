#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); // RX, TX
char character;
int count = 0;
void setup()  
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() // run over and over
{
    //String Data = "";
    //Serial.print(mySerial.read());
    
    while(mySerial.available()) {
     character = mySerial.read();
     //Data.concat(character);
     mySerial.println(character);
     Serial.println(character);
     digitalWrite(2,1);
     digitalWrite(3,1);
     delay(1000);
     
     //count++;
    }
    digitalWrite(2,0);
     digitalWrite(3,0);
    Serial.print("S\n");
    mySerial.print("a\n");
    delay(1000);
}
