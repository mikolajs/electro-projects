#include "BMP280lib.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
//create an BMx280 object using the SoftWire Interface
BMx280SoftWire bmx280(I2C_ADDRESS);
String serverName = "http://192.168.0.120:8989/set-temperature";

double pressure = 0.0;
double tempBmx = 0.0;
double tempDht = 0.0;
double humidityDht = 0.0;

const int dhtpin = 2;
DHT dht(dhtpin, DHT22);

void connectWifi(){
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

void setup() {
  Serial.begin(9600);
  connectWifi();

  dht.begin();
  //wait for serial connection to open (only necessary on some boards)
  while (!Serial);
  
  //SoftWire setup
  sw.setDelay_us(5);
  sw.setTimeout_ms(100);
  sw.begin();
  if (!bmx280.begin())
  {
    Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
    while (1);
  }
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);
  if (bmx280.isBME280())
    bmx280.writeOversamplingHumidity(BMx280MI::OSRS_H_x16);
}

bool measures(){
  if (!bmx280.measure()) {
    Serial.println("could not start measurement, is a measurement already running?");
    return false;
  }
  do {
    delay(100);
  } while (!bmx280.hasValue());
  pressure = bmx280.getPressure64();
  tempBmx = bmx280.getTemperature();
  tempDht = dht.readTemperature();
  humidityDht = dht.readHumidity();
  Serial.print("Pressure (64 bit): "); 
  Serial.println(pressure);
  Serial.print("Temperature BMX: "); 
  Serial.println(tempBmx);
  Serial.print("Temperature DHT: "); 
  Serial.println(tempDht);
  Serial.print("Humidity DHT: "); 
  Serial.println(humidityDht);
  return true;
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      measures();
      String serverPath = serverName;
      String json = "{ \"station\":\"withBmx\", \"data\":{";
      json += "\"temperatureBmx\":";
      json += String(tempBmx, 2);
      json +=  ", "; 
      json += "\"temperatureDht\":";
      json +=  String(tempDht,2);
      json += ", ";
      json +=  "\"pressureBmx\":";
      json += String(pressure, 2);
      json += ", ";
      json += "\"humidityDht\":";
      json += String(humidityDht, 2);
      json += "}}\n";
      //serverPath += json;

      http.begin(client, serverPath.c_str());
      Serial.println(serverPath);
      http.addHeader("Content-Type", "application/json");
      //Serial.println(json);
      int httpResponseCode = http.POST(json);
      
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
      delay(100000);
    }
    else {
      Serial.println("WiFi Disconnected");
      connectWifi();
    }
  
  delay(20000);

}
