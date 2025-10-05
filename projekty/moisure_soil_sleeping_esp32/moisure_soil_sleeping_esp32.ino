//wetknąć tak aby 6 cm zostału u góry. 
#include <esp_sleep.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#define SENSOR_PIN 4
#define TIME_TO_SLEEP  8640

void connectWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin("sweethome12", "9A0033D4");
  Serial.print("Connecting to ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendData(int moisure){
  if(WiFi.status() != WL_CONNECTED){
    connectWifi();
  }
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/setMoistureInfo?d=yellow11&m=";
      serverPath += String(moisure);
      http.begin(wifi, serverPath.c_str());
      Serial.println(serverPath);
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
      //opdelay(1000);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void setup() {
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  int val = analogRead(SENSOR_PIN);
  Serial.print("Soil moisure val = ");
  Serial.println(val);
  sendData(val);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000ULL);
  Serial.println("Go to sleep...");
  Serial.flush();
  delay(100);
  esp_deep_sleep_start();
  delay(100);
  Serial.println("Cannot sleep!");
}

