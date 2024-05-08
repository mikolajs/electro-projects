#include <FastLED.h>
#define LED_PIN 5    // Replace with the pin number you used for DATA connection
#define NUM_LEDS 50  // Replace with the number of LEDs in your strip
#define DELAY_TIME 20  // Delay between LED movements (in milliseconds)

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}
void loop() {
  // Turn off all LEDs
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
}
