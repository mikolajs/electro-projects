//generic esp8266 module
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//filotetowa do 04, a niebieska do 05
/* Use software serial for the PZEM
 * Pin 11 Rx (Connects to the Tx pin on the PZEM)
 * Pin 12 Tx (Connects to the Rx pin on the PZEM)
*/

SoftwareSerial pzemSWSerial(4, 5);
PZEM004Tv30 pzem;
int t = 0;
#define ATIME 30000
float voltage ;
float current;
float power;
float energy;
float frequency;
float pf;

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

void printDataPZEM(){
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
        Serial.println();
}

String readDataPZEM(){
  voltage = pzem.voltage();
  current = pzem.current();
  power = pzem.power();
  energy = pzem.energy();
  frequency = pzem.frequency();
  pf = pzem.pf();
  if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {
      String getStr;
      getStr += "&v=";
      getStr += String(voltage);
      getStr += "&a=";
      getStr += String(current);
      getStr += "&p=";
      getStr += String(power);
      getStr += "&e=";
      getStr += String(energy);
      getStr += "&f=";
      getStr += String(frequency);
      getStr += "&x=";
      getStr += String(pf);
      return getStr;
    }
    return "";
}

void mkMeasureAndSendInfo(){
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/addpowerinfo?m=measuretest1";
      String measureStr = readDataPZEM();
      if(measureStr.length() > 3){
         serverPath += measureStr;
         http.begin(wifi, serverPath.c_str());
           Serial.println(serverPath);
         //Serial.println(json);
          int httpResponseCode = http.GET();
          if (httpResponseCode > 0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        } else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
      } else {
        Serial.println("Error reading PZEM004 data");
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
  pzem = PZEM004Tv30(pzemSWSerial);
  Serial.println(pzem.readAddress(), HEX);
  pzem.resetEnergy();
  connectWifi();
}

void loop() {
    //digitalWrite(16, HIGH);   
    Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);
    mkMeasureAndSendInfo();
    printDataPZEM();
    delay(ATIME);
}