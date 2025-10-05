///ESP32 Mini
#include <WiFi.h>
#include <HTTPClient.h>
#define POMP1 1
#define POMP1_TIME 4000
#define POMP2 2
#define POMP2_TIME 4000
//in seconds!!!!
#define HOUR 3600
const char* ssid = "sweethome12";
const char* password = "9A0033D4";

void setup() {
  Serial.begin(115200);
  pinMode(POMP1, OUTPUT);
  pinMode(POMP2, OUTPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void mkWater(){
  Serial.println("Water");
  digitalWrite(POMP1, HIGH);
  delay(POMP1_TIME);
  digitalWrite(POMP1, LOW);
  digitalWrite(POMP2, HIGH);
  delay(POMP2_TIME);
  digitalWrite(POMP2, LOW);
  
  
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient wifi;
    HTTPClient http;
    String serverPath =  "http://192.168.0.120:8989/setWateringInfo?d=dom";
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

void loop() {
  delay(10000);
  //Serial.print(period);
  //Serial.print()

  if(WiFi.status()== WL_CONNECTED){
    WiFiClient wifi;
    HTTPClient http;
    String serverPath =  "http://192.168.0.120:8989/canWatering?d=dom";
    http.begin(wifi, serverPath.c_str());
    Serial.println(serverPath);
    int httpResCode = http.GET();
    if(httpResCode == 200) {
      Serial.println("Watering time now");
      http.end();
      mkWater();
    }
    else {
      Serial.print("No watering time code: ");
      Serial.println(String(httpResCode));
      http.end();
    }
    delay(HOUR*1000);
  } else {
    delay(1000);
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
  //delay(1000);
}
