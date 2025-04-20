const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int pressed = 0;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
 
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    pressed++;
    
  } else {
    if(pressed > 0) pressed--;
    //in clock pressed = 0;
    //and use pressed to move quicker
  }
  if(pressed > 1) {
    digitalWrite(ledPin, HIGH);
  } else digitalWrite(ledPin, LOW);
  delay(50);
 
}
