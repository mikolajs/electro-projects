//ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define POMP1 0 ///newer use pin 2!!!
#define POMP1_TIME 7000

//in seconds!!!!
#define HOUR 3600
const char* ssid = "sweethome12";
const char* password = "9A0033D4";
void setup() {
  Serial.begin(115200);
  pinMode(POMP1, OUTPUT);
  
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
  delay(POMP1_TIME);
  
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient wifi;
    HTTPClient http;
    String serverPath =  "http://192.168.0.120:8989/setWateringInfo?d=juka";
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
    String serverPath =  "http://192.168.0.120:8989/canWatering?d=juka";
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
