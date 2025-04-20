#include <Wire.h>
#include <SoftwareSerial.h>
#include <Suli.h>
#include <Four_Digit_Display_Arduino.h>


Four_Digit_Display_Arduino    disp;

int a = 0;
int b = 0;
void setup()
{
    disp.begin(2, 3);
    disp.display(1, 14);
}


void loop()
{
  
 disp.display(a, b);
 if(a > 11) {b++; a = 0;}
 a++;
 delay(1000);
}
