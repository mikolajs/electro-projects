/* mq2 gaz i dym – reaguje tylko przy mocnym gazie i dymie
przy piecyku gazowym, sprawdzam dym, gaz i temperaturę
*/
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

DHT dht(2, DHT22);
int valueAnalog = 0;
int valueMap = 0;
int analogPin = 0; 
double HUM = 0.0;
double TEM = 0.0;
int SMO = 0;

bool measure(){
  HUM = dht.readHumidity();
  TEM = dht.readTemperature();
  Serial.println("t = " + String(TEM, 2) + " h = " + String(HUM, 2));
  if(TEM == NAN || HUM == NAN) return false;
  else return true;
}

void connectWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin("sweethome12", "9A0033D4");
  Serial.print("Connecting to ");
  Serial.println("sweethome12");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendData(double t, double h, double s){
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/sensor?th=piecyk&T=";
      serverPath += String(t,2);
      serverPath += "&h=";
      serverPath += String(h, 2);
      serverPath += "&s=";
      serverPath += String(s, 2);
      http.begin(wifi, serverPath.c_str());
      Serial.println(serverPath);
      //Serial.println(json);
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
      connectWifi();
    }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(100);
}

void loop() {
  connectWifi();
  SMO = analogRead(analogPin);
  //valueMap = map(valueAnalog, 0, 1023, 0, 100);
  String info = "MQ2 read: " + String(valueAnalog);
  if(valueAnalog > 1100){
    Serial.print(info);
    Serial.println(" Wykryto gaz lub CO");
  } else {
    Serial.println(info);
  }
  measure();
  sendData(TEM, HUM, SMO);
  delay(180000);
}
