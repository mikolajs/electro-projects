#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define POMP1 0
#define POMP1_TIME 1000
uint32_t wakeCounter = 0;
uint32_t rtcMemoryOffset = 0;
//const int sleepTimeSeconds = 12086; // Example: 3 hours and 21 minutes and 26 seconds
const int sleepTimeSeconds = 60;
const uint64_t sleepTimeMicroseconds = (uint64_t)sleepTimeSeconds * 1000000ULL;
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
  Serial.begin(9600);
  while(!Serial){}
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
  Serial.println(h);
  if (h >= 20) mkWater();
  digitalWrite(POMP1, LOW);
  ESP.deepSleep(30e6);
}

void loop() {
}
