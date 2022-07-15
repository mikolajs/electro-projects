
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

const char* ssid     = "sweethome12";
const char* password = "9A0033D4";
const char* url = "/set/1";
const char* host = "192.168.0.104:9900";  

const int station = 1;
const int dhtpin = 2;
DHT dht(dhtpin, DHT22);
float t = 0;
float h = 0;
int lastCommand = 0;


void sendTemp(){
  WiFiClient w;
  HTTPClient client;
  String address = "http://192.168.0.104:9900/set/";
  address += station;
  address += "?t=";
  address += String(t, 2) + "&h=" + String(h, 2); 
  client.begin(w, address.c_str());
  Serial.println(address);
  Serial.println(t);
  Serial.println(h);
  int httpResponseCode =  client.GET();
  if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = client.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
  client.end();
}




void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 
  dht.begin();
}

void loop() {
  delay(2000);
  if((millis() - lastCommand) >= 2000){
      lastCommand = millis();
      t = dht.readTemperature();
      h = dht.readHumidity();
    }
  sendTemp();
  delay(100);
  //Serial.println(millis() - lastCommand);
  
    Serial.println("SLEEP");
    //ESP.deepSleep(6000000); 
    Serial.println("AWAKE");
}
