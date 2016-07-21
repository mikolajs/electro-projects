#include <Wire.h>

#include <Wire.h>
    #include "DS3231.h"
     
    DS3231 clock;
    RTCDateTime dt;
     
    void setup()
    {
      Serial.begin(9600);
     
      // Inicjalizacja DS3231
      Serial.println("Initialize DS3231");;
      clock.begin( );
      //pinMode(1, OUTPUT); 
      for(int i = 22; i < 34; i++) 
        pinMode(i, OUTPUT); 
      // Ustawiany date i godzine kompilacji szkicu
       clock.setDateTime(__DATE__, __TIME__);
    }
    
     
    void loop()
    {
      // Odczytujemy i wyswietlamy czas
      dt = clock.getDateTime();
     
      Serial.print("Raw data: ");
      Serial.print(dt.year);   Serial.print("-");
      Serial.print(dt.month);  Serial.print("-");
      Serial.print(dt.day);    Serial.print(" ");
      Serial.print(dt.hour);   Serial.print(":");
      Serial.print(dt.minute); Serial.print(":");
      Serial.print(dt.second); Serial.println("");
     
      /*
      if( dt.second % 2 == 0)
        digitalWrite(33, LOW);
      else
        digitalWrite(33, HIGH);
         */
        
      int temp = dt.minute;
      for(int i = 27; i < 33; i++){
        if(temp % 2 == 0) digitalWrite(i, LOW);
        else digitalWrite(i, HIGH);
        temp /= 2;
      }
      temp =  dt.hour;
      for(int i = 22; i < 27; i++) {
        if(temp % 2 == 0) digitalWrite(i, LOW);
        else digitalWrite(i, HIGH);
        temp /= 2;
      }
      delay(1000);
     
    }

