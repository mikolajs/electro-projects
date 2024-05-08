#include <FastLED.h>
#define LED_PIN 5    // Replace with the pin number you used for DATA connection
#define NUM_LEDS 50  // Replace with the number of LEDs in your strip
#define DELAY_TIME 20  // Delay between LED movements (in milliseconds)

#include <Adafruit_NeoPixel.h>
#define PIN            15
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN,
NEO_GRB + NEO_KHZ800);

CRGB leds[NUM_LEDS];
int animation = 0;
int colorsGrid[30] = {CRGB::Amethyst, CRGB::Aqua, CRGB::Blue, CRGB::BlueViolet, CRGB::Brown, CRGB::CadetBlue,
 CRGB::Chartreuse, CRGB::Coral, CRGB::CornflowerBlue, CRGB::Cornsilk, CRGB::Crimson, CRGB::DarkBlue, 
 CRGB::DarkGoldenrod, CRGB::DarkMagenta, CRGB::DarkOrange, CRGB::Gold, CRGB::GreenYellow, CRGB::Ivory, 
 CRGB::Khaki, CRGB::LawnGreen, CRGB::LightBlue, CRGB::LightSkyBlue, CRGB::Maroon, CRGB::OrangeRed, CRGB::Orange,
 CRGB::PaleGreen, CRGB::Pink, CRGB::Pink, CRGB::SeaGreen, CRGB::SkyBlue }; 

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
    delay(50);
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
    delay(300);
  }
}

void colorLight() {
  uint8_t pow = 120;
  for (int i = 0; i < NUMPIXELS; i++) {
    setRed(i, pow);
  }
  delay(500);
  for (int i = 0; i < NUMPIXELS; i++) {
    setGreen(i, pow);
  }
  delay(500);
  for (int i = 0; i < NUMPIXELS; i++) {
    setYellow(i, pow);
  }
  delay(500);
  for (int i = 0; i < NUMPIXELS; i++) {
    setBlue(i, pow);
  }
  delay(500);
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
    delay(40);
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

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
   pixels.begin();
  randomSeed(analogRead(0));
}
void loop() {
  // Turn off all LEDs
  switch(animation){
    case 0:
    off();
    snakeMoveColor();
    break;
     case 1:
     off();
     snakeMove();
     break;
     case 2:
    off();
    lightDark();
    break;
     case 3:
    off();
    colorLight();
    break;
     case 4:
    off();
    colorLight();
    break;
    case 5:
    off();
    randomColor();
    break;
    default:
     animation = 0;
     break;
  }
  animation++;
  animation %= 6;
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  // Move the LED chaser
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;  // Set the current LED to blue
    FastLED.show();  // Update the LED strip
    delay(DELAY_TIME);  // Delay between LED movements
  }
  // Move the LED chaser in reverse
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB::Green;  // Set the current LED to green
    FastLED.show();  // Update the LED strip
    delay(DELAY_TIME);  // Delay between LED movements
  }
  delay(DELAY_TIME*2);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;  // Set the current LED to blue
    FastLED.show();  // Update the LED strip
    delay(DELAY_TIME);  // Delay between LED movements
  }
  // Move the LED chaser in reverse
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB::Fuchsia;  // Set the current LED to green
    FastLED.show();  // Update the LED strip
    delay(DELAY_TIME);  // Delay between LED movements
  }
  delay(DELAY_TIME*2);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
   delay(DELAY_TIME);
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = colorsGrid[random(30)];  // Set the current LED to green
    FastLED.show();  // Update the LED strip
    
  }
     // Delay between LED movements
   delay(DELAY_TIME);

}
