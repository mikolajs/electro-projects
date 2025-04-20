/* Blink without Delay
 
 Turns on and off a light emitting diode(LED) connected to a digital  
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
 
 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.
 
 
 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 
 This example code is in the public domain.

 
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */


long previousMillis = 0;        // will store last time LED was updated

long interval =  200;           // interval at which to blink (milliseconds)

void setup() {
  for(int i = 22; i < 34; i++)
  pinMode(i, OUTPUT);    
}
int now = 32;

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
  
  
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    digitalWrite(now, LOW);
    if(now == 32) now = 22;
    else now++;
    digitalWrite(now, HIGH);
    if(now % 2 == 0) digitalWrite(33, HIGH);
    else digitalWrite(33, LOW);
  }
  
}

