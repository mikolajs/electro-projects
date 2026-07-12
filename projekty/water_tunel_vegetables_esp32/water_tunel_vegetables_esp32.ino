//esp32-wroom-da module
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define POMP1 23
#define POMP1_TIME 10000
RTC_DATA_ATTR int bootCount = 0;
// uint32_t wakeCounter = 0;
// uint32_t rtcMemoryOffset = 0;
//const int sleepTimeSeconds = 12086; // Example: 3 hours and 21 minutes and 26 seconds
#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  3600    
const char* ssid = "sweethome12";
const char* password = "9A0033D4";
// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP);

// void mkWater() {
//   for (int i = 0; i < 5; i++) {
//     digitalWrite(POMP1, HIGH);
//     delay(POMP1_TIME);
//     ++bootCount;
//     //aTime += 2*POMP1_TIME;
//     digitalWrite(POMP1, LOW);
//     delay(POMP1_TIME);
//   }
// }
void checkIfWater(){
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient wifi;
    HTTPClient http;
    String serverPath =  "http://192.168.0.120:8989/canWatering?d=tunel";
    http.begin(wifi, serverPath.c_str());
    Serial.println(serverPath);
    int httpResCode = http.GET();
    if(httpResCode == 200) {
      Serial.println("Watering time now");
      http.end();
      mkWaterIothome();
    }
    else {
      Serial.print("No watering time code: ");
      Serial.println(String(httpResCode));
      http.end();
    }
    delay(100);
  } else {
    delay(1000);
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }

}

void mkWaterIothome(){
  Serial.println("Water");
  for(int i = 0; i < 5; i++){
    digitalWrite(POMP1, HIGH);
    delay(POMP1_TIME);
    digitalWrite(POMP1, LOW);
    delay(POMP1_TIME);
  }

  if(WiFi.status()== WL_CONNECTED){
    WiFiClient wifi;
    HTTPClient http;
    String serverPath =  "http://192.168.0.120:8989/setWateringInfo?d=tunel";
    http.begin(wifi, serverPath.c_str());
    Serial.println(serverPath);
    int httpResCode = http.GET();
    if(httpResCode == 200) Serial.println("Set info OK");
    else {
      Serial.print("Error set info code: ");
      Serial.println(String(httpResCode));
    }
    http.end();
 }
}


// void waterWihTimer(){
//   timeClient.begin();
//   timeClient.update();
//   int h = timeClient.getHours();
//    if (h >= 16 && bootCount == 0) mkWater();
//   else bootCount = 0;
// }

void setup() {
  pinMode(POMP1, OUTPUT);
    Serial.begin(115200);
   delay(1000);
  // while(!Serial){}
  //++bootCount;
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  Serial.println("Boot count: " + String(bootCount));
  digitalWrite(POMP1, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Serial.println("");
  Serial.println("WiFi connected");
  delay(1000);
  checkIfWater(); // check serwer if should water, and if should start mkWater and send info to serwer
  //mkWater();
  digitalWrite(POMP1, LOW);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.print("Go to sleep for ");
  Serial.println(String(TIME_TO_SLEEP * uS_TO_S_FACTOR));
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
}
