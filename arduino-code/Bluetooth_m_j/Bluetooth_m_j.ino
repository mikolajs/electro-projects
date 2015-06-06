#include <SoftwareSerial.h>// import the serial library

SoftwareSerial mojserial(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  mojserial.begin(9600);
  mojserial.println("Aby wlaczyc diode wpisz 1 lub 0 aby ja wylaczyc");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (mojserial.available()){
BluetoothData=mojserial.read();
   if(BluetoothData=='1'){   // if number 1 pressed ....
   digitalWrite(ledpin,1);
   mojserial.println("LED On ! ");
   }
  if (BluetoothData=='0'){// if number 0 pressed ....
  digitalWrite(ledpin,0);
   mojserial.println("LED Off ! ");
  }
}
delay(100);
}
