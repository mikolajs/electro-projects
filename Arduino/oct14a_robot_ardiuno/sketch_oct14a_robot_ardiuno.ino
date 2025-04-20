
//The setup function is called once at startup of the sketch
#define btn 2
#define l1 9
#define l2 10

void setLeds();

int8_t leds = 3;
int power = 1023;

void setup(){
  //setLeds();
 Serial.begin(9600);
 pinMode(btn, INPUT_PULLUP);
 pinMode(l1, OUTPUT);
 pinMode(l2, OUTPUT);
 pinMode(A0, OUTPUT);
 analogWrite(l1, power);
 analogWrite(l2, power);
}

void loop(){
  setLeds();
  power = analogRead(A0);

  Serial.print(power);
  Serial.print(" ");
//  if(digitalRead(btn) == LOW){
//    delay(50);
//    if(digitalRead(btn) == LOW){
//      if(leds < 3) leds++;
//      else leds = 0;
//      setLeds();
//      delay(200);
//    }
//  }
  delay(1000);
}

void setLeds(){
  switch(leds){
  case 3:
    analogWrite(l1, power);
    analogWrite(l2, power);
    break;
  case 2:
    analogWrite(l1, 0);
    analogWrite(l2, power);
    break;
  case 1:
    analogWrite(l1, power);
    analogWrite(l2, 0);
    break;
  default:
    analogWrite(l1, 0);
    analogWrite(l2, 0);
    break;
  }
}

