#include <Adafruit_NeoPixel.h>
#define PIN            15
#define NUMPIXELS      25
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500;

void setup() {
  pixels.begin();
  randomSeed(analogRead(0));
}

void setColor(uint8_t nr, uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(nr, pixels.Color(r, g, b));
  pixels.show();
}

void setRed(int nr, uint8_t pow) {
  setColor(nr, pow, 0, 0);
}

void setGreen(int nr, uint8_t pow) {
  setColor(nr, 0, pow, 0);
}

void setBlue(int nr, uint8_t pow) {
  setColor(nr, 0, 0, pow);
}

void setYellow(int nr, uint8_t pow) {
  setColor(nr, pow, pow, 0);
}

void setViolet(int nr, uint8_t pow) {
  setColor(nr, pow, 0, pow);
}

void setMarine(int nr, uint8_t pow) {
  setColor(nr, 0, pow, pow);
}

void setOrange(int nr, uint8_t pow) {
  uint8_t g = pow * 2 / 3;
  setColor(nr, pow, g, 0);
}

void switchOff(int nr) {
  setColor(nr, 0, 0, 0);
}

void lightDark() {
  for (uint8_t p = 1; p < 250; p += 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 4 == 0)
        setRed(i, p);
      else if (i % 4 == 1)
        setBlue(i, p);
      else if (i % 4 == 2)
        setGreen(i, p);
      else if (i % 4 == 3)
        setYellow(i, p);
    }
    delay(100);
  }
}

void rondo() {
  uint8_t p = 120;
  for (int b = 0; b < 32; b++) {
    int nr = b % NUMPIXELS;
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 4 == 0)
        setRed((i + nr) % NUMPIXELS, p);
      else if (i % 4 == 1)
        setBlue((i + nr) % NUMPIXELS, p);
      else if (i % 4 == 2)
        setGreen((i + nr) % NUMPIXELS, p);
      else if (i % 4 == 3)
        setYellow((i + nr) % NUMPIXELS, p);
    }
    delay(500);
  }
}

void colorLight() {
  uint8_t pow = 120;
  for (int i = 0; i < NUMPIXELS; i++) {
    setRed(i, pow);
  }
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    setGreen(i, pow);
  }
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    setYellow(i, pow);
  }
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    setBlue(i, pow);
  }
  delay(1000);
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
          setColor(i, r, g, b);
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
          setMarine(i, pow);
          break;
        case 7:
          setBlue(i, pow);
          break;
        default:
          setColor(i, pow, pow, pow);
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

void randomColor() {
  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      setColor(i, random(120), random(120), random(120));
    }
    delay(1000);
  }
}

void off() {
  for (int i = 0; i < NUMPIXELS; i++) {
    switchOff(i);
  }
}

void loop() {
  snakeMoveColor();
  off();
  snakeMove();
  off();
  delay(delayval);
  lightDark();
  off();
  delay(delayval);
  colorLight();
  off();
  delay(delayval);
  rondo();
  colorLight();
  delay(delayval);
  randomColor();
  delay(delayval);
}
