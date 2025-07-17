//esp32-wroom-da module
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define POMP1 12
#define POMP1_TIME 3000
//RTC_DATA_ATTR int bootCount = 0;
uint32_t wakeCounter = 0;
uint32_t rtcMemoryOffset = 0;
//const int sleepTimeSeconds = 12086; // Example: 3 hours and 21 minutes and 26 seconds
#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  10800    
const char* ssid = "sweethome12";
const char* password = "9A0033D4";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void mkWater() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(POMP1, HIGH);
    delay(POMP1_TIME);
    //aTime += 2*POMP1_TIME;
    digitalWrite(POMP1, LOW);
    delay(POMP1_TIME);
  }
}

void setup() {
  pinMode(POMP1, OUTPUT);
  // Serial.begin(115200);
  delay(1000);
  // while(!Serial){}
  //++bootCount;
  // Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  // Serial.println("Boot count: " + String(bootCount));
  digitalWrite(POMP1, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  timeClient.begin();
  timeClient.update();
  int h = timeClient.getHours();
  // Serial.println(h);
  if (h >= 21) mkWater();
  digitalWrite(POMP1, LOW);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // Serial.print("Go to sleep");
  delay(1000);
  // Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
}
