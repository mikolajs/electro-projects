//wetknąć tak aby 6 cm zostału u góry. 
//podłączyć przełącznik do 5V
#include <esp_sleep.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#define SENSOR_PIN 4
#define DRY_THRESHOLD 2400
#define WATERING_TIME 3000 //ms
#define VALVE_PIN 0
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  1800  

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

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void sendData(int moisure){
  if(WiFi.status() != WL_CONNECTED){
    connectWifi();
  }
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/setWateringInfo?d=relay1&m=";
      serverPath += String(moisure);
      http.begin(wifi, serverPath.c_str());
      Serial.println(serverPath);
      //Serial.println(json);oid print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}
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

void mkWatering(){
  Serial.println("watering");
  digitalWrite(VALVE_PIN, HIGH);
  delay(WATERING_TIME);
  digitalWrite(VALVE_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(VALVE_PIN, LOW);
  connectWifi();
}

void loop() {
  int val = analogRead(SENSOR_PIN);
  Serial.print("Soil moisure val = ");
  Serial.println(val);
  if(val < DRY_THRESHOLD) {
    mkWatering();
    sendData(val);
  }
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Go to sleep...");
  Serial.flush();
  delay(100);
  esp_deep_sleep_start();
  delay(100);
  Serial.println("Cannot sleep!");
}
