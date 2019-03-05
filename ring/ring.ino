#include <Adafruit_NeoPixel.h>

#define PIN            3
#define NUMPIXELS      16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN,
NEO_GRB + NEO_KHZ800);

void setup() {
    pixels.begin();
    randomSeed(analogRead(0));
}

void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t pin){
  pixels.setPixelColor(pin, pixels.Color(r, g, b));
  pixels.show();
}

void setBlue(uint8_t pin, uint8_t power){
  setColor(0, 0, power, pin);
}

void setGreen(uint8_t pin, uint8_t power){
  setColor(0, power, 0, pin);
}

void setRed(uint8_t pin, uint8_t power){
  setColor(power, 0, 0, pin);
}

void setYellow(uint8_t pin, uint8_t power){
  setColor(power, power, 0, pin);
}

void setNavy(uint8_t pin, uint8_t power){
  setColor(0, power, power, pin);
}

void setViolet(uint8_t pin, uint8_t power){
  setColor(power, 0, power, pin);
}

void setOrange(uint8_t pin, uint8_t power){
  int g = (2*power)/5;
  setColor(power,g, 0, pin); 
}

void setPink(uint8_t pin, uint8_t power){
  int c = (power)/7;
  setColor(power,c, c, pin); 
}

void switchOff(int nr) {
  setColor(0, 0, 0, nr);
}

void rainbow(uint8_t p, uint8_t trans){
  trans %= 8;
  uint8_t r = 0;
  for(uint8_t i = 0; i < NUMPIXELS; i++){
    r = (i+ trans) % 8;
    switch(r){
      case 0: 
      setRed(i, p);
      break;
      case 1: 
      setBlue(i, p);
      break;
      case 2: 
      setGreen(i, p);
      break;
      case 3: 
      setYellow(i, p);
      break;
      case 4: 
      setNavy(i, p);
      break;
      case 5: 
      setOrange(i, p);
      break;
      case 6: 
      setViolet(i, p);
      break;
      default: 
      setPink(i, p);
      break;
    }
  }
}

void darkLight(){
  uint8_t p = 0;
  uint8_t d = 5;
  float f = 1.2f;
  for(int i = 0; i < 8; i++){
    p = 5;
    for(; p <= 250;){
      rainbow(p, i);
      p = (uint8_t) p*f;
      delay(d);
    }
    p = 250;
    for(; p >= 5;){
      rainbow(p, i);
      p = (uint8_t) p/f;
      delay(d);
    }
  }
}

void rainbowMove(){
  for(int i = 0; i < 1000; i++){
    rainbow(120, i);
    delay(100);
  }
}

void rainbowMoveUpAndDown(){
  for(int i = 0; i < 100; i++){
    rainbow(120, i);
    delay(i % 50 + 50);
  }
}


void randomColor(){
  uint8_t p = 120;
   for (int i = 0; i < NUMPIXELS; i++) {
      setColor(random(120), random(120), random(120), i);
  }
  delay(50);
  for(int i = 0; i < 500; i++){
    setColor(random(p), random(p), random(p), random(NUMPIXELS));
    delay(50);
  }
}

void colorLight() {
  uint8_t pow = 120;
  int d = 600;
  for(int j = 0; j < 9; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
    setRed(i, pow);
  }
  delay(d);
  for (int i = 0; i < NUMPIXELS; i++) {
    setGreen(i, pow);
  }
  delay(d);
  for (int i = 0; i < NUMPIXELS; i++) {
    setYellow(i, pow);
  }
  delay(d);
  for (int i = 0; i < NUMPIXELS; i++) {
    setBlue(i, pow);
  }
  delay(d);
  for (int i = 0; i < NUMPIXELS; i++) {
    setOrange(i, pow);
  }
  delay(d);
  for (int i = 0; i < NUMPIXELS; i++) {
    setViolet(i, pow);
  }
  delay(d);
  for (int i = 0; i < NUMPIXELS; i++) {
    setNavy(i, pow);
  }
  delay(d);
   d -= 60;
  }
  
}

boolean snakeIfOnLed(int i, uint8_t start, uint8_t end, uint8_t N) {
  if (i >= start) {
    if (i < start + N)
      return true;
    else
      return false;
  } else {
    if (end < start) {
      if (i < end)
        return true;
      else
        return false;
    } else
      return false;
  }
  return true;
}

void snakeMove() {
  uint8_t pow = 120;
  uint8_t NUMB = 10;
  uint8_t start = 0;
  uint8_t end = NUMB;
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  for (int k = 1; k < 7; k++) {
    if ((k & 1) > 0)
      r = pow;
    else
      r = 0;
    if ((k & 2) > 0)
      g = pow;
    else
      g = 0;
    if ((k & 4) > 0)
      b = pow;
    else
      b = 0;
    for (int j = 0; j < 64; j++) {
      end = (start + NUMB) % NUMPIXELS;
      for (int i = 0; i < NUMPIXELS; i++) {
        if (snakeIfOnLed(i, start, end, NUMB))
          setColor(r, g, b, i);
        else
          switchOff(i);
      }
      start++;
      start %= NUMPIXELS;
      delay(50);
    }
  }
}

void snakeMoveColor() {
  uint8_t pow = 120;
  uint8_t NUMB = 8;
  uint8_t start = 0;
  uint8_t end = NUMB;
  uint8_t pos = 0;
  for (int j = 0; j < 320; j++) {
    end = (start + NUMB) % NUMPIXELS;
    for (int i = 0; i < NUMPIXELS; i++) {
      if (snakeIfOnLed(i, start, end, NUMB)) {
        if (i >= start)
          pos = i - start;
        else
          pos = i + NUMPIXELS - start;
        switch (pos) {
        case 0:
          setRed(i, pow);
          break;
        case 2:
          setOrange(i, pow);
          break;
        case 3:
          setYellow(i, pow);
          break;
        case 4:
          setViolet(i, pow);
          break;
        case 5:
          setGreen(i, pow);
          break;
        case 6:
          setNavy(i, pow);
          break;
        case 7:
          setBlue(i, pow);
          break;
        default:
          setColor(0, 0, 0, i);
          break;
        }
      } else
        switchOff(i);
    }
    start++;
    start %= NUMPIXELS;
    delay(50);
  }
}


void flash(){
  for(int i = 0; i < 600; i++){
    if(i % 3 == 0) switchOff(i % NUMPIXELS);
    else setBlue(i % NUMPIXELS, 120);
    delay(4);
  }
  for(int i = 0; i < 600; i++){
    if(i % 3 == 0) switchOff(i % NUMPIXELS);
    else setRed(i % NUMPIXELS, 120);
    delay(4);
  }
  for(int i = 0; i < 600; i++){
    if(i % 3 == 0) switchOff(i % NUMPIXELS);
    else setGreen(i % NUMPIXELS, 120);
    delay(4);
  }
  for(int i = 0; i < 600; i++){
    if(i % 3 == 0) switchOff(i % NUMPIXELS);
    else setYellow(i % NUMPIXELS, 120);
    delay(4);
  }
  for(int i = 0; i < 600; i++){
    if(i % 3 == 0) switchOff(i % NUMPIXELS);
    else setViolet(i % NUMPIXELS, 120);
    delay(4);
  }
}


void loop() {
   colorLight();
   delay(50);
   randomColor();
   delay(50);
   rainbowMoveUpAndDown();
   delay(50);
   darkLight();
   delay(50);
   flash();
   delay(50);
   snakeMove();
   delay(50);
   snakeMoveColor();
   delay(50);
   for (int i = 0; i < NUMPIXELS; i++)
     switchOff(i);
   delay(1000);

}
