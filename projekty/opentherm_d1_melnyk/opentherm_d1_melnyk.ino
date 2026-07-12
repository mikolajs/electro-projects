#include <OpenTherm.h>
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define WAIT  180000 /*in miliseconds*/        
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

float CH_SETPOINT = 30.0f;
//podłączenie kabli: czerwony -    , zielony -
OpenTherm ot(4, 5);  // (2, 3)??
uint32_t currentTime = 0;
uint32_t previousTime = 0;
uint32_t timePass = 0;
uint32_t sendDataTime = 0;
int step = 0;
float boilerTemperature = 0.0f;
float returnTemperature = 0.0f;
float dhwTemperature = 0.0f;

void ICACHE_RAM_ATTR handleInterrupt() {
  ot.handleInterrupt();
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("START");
  connectWifi();
  ot.begin(handleInterrupt);
  sendDataTime = WAIT;
  previousTime = millis();
}

void getTemperature(){
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/boiler";
      http.begin(wifi, serverPath.c_str());
      Serial.println(serverPath);
      //Serial.println(json);
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        float Temp = payload.toFloat();
        CH_SETPOINT = roundf(Temp*10.0f)/10.0f;
      //  if(!ot.write(OpenTherm::WRITE_DATA_ID::DHW_SETPOINT, Temp)) {
      //   Serial.printf("Failed to set Central Heating (CH) temperature setpoint to %.01f *C\n", CH_SETPOINT);
      //  } else Serial.printf("Sucessly set temp %01f *C\n", Temp);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        // if(!ot.write(OpenTherm::WRITE_DATA_ID::CONTROL_SETPOINT_CH, 30.0f)) {
        //   Serial.printf("Failed to set Central Heating (CH) temperature setpoint to %.01f *C\n", CH_SETPOINT);
        // } else Serial.printf("Error HTTTP, set temp 30*C\n");
      }
      // Free resources
      http.end();
      //opdelay(1000);
    } else {
      Serial.println("WiFi Disconnected");
      connectWifi();
    }
}

void setBoilerInfo(){
  if(WiFi.status()== WL_CONNECTED){
      getStatus();
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/addboilerinfo?rwt=";
      serverPath += String(returnTemperature);
      serverPath += "&bwt=";
      serverPath += String(boilerTemperature);
      serverPath += "&spb=0";
      serverPath += "&oemd=0";
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

void getStatus(){
  boilerTemperature = ot.getBoilerTemperature();
  returnTemperature = ot.getReturnTemperature();
  dhwTemperature = ot.getDHWTemperature();
}

void showStatus(){
  getStatus();
  Serial.print("boiler temp: ");
  Serial.print(boilerTemperature);
  Serial.print("°C, return temp: ");
  Serial.print(returnTemperature);
  Serial.println("°C");
  Serial.println("DHW temperature is " + String(dhwTemperature) + " degrees C");
}

void loop() {
  //getTemperature();
  currentTime = millis();
  timePass = (uint32_t)(currentTime - previousTime);
  if(timePass >= 1000) {
    sendDataTime += timePass;
    previousTime = currentTime;
    bool enableCentralHeating = true;
    bool enableHotWater = false;
    bool enableCooling = true;
    unsigned long response = ot.setBoilerStatus(enableCentralHeating, enableHotWater, enableCooling);
    OpenThermResponseStatus responseStatus = ot.getLastResponseStatus();
    if (responseStatus == OpenThermResponseStatus::SUCCESS){
        Serial.println("Central Heating: " + String(ot.isCentralHeatingActive(response) ? "on" : "off"));
        Serial.println("Hot Water: " + String(ot.isHotWaterActive(response) ? "on" : "off"));
        Serial.println("Flame: " + String(ot.isFlameOn(response) ? "on" : "off"));
    }
    if (responseStatus == OpenThermResponseStatus::NONE){
        Serial.println("Error: OpenTherm is not initialized");
    }
    else if (responseStatus == OpenThermResponseStatus::INVALID){
        Serial.println("Error: Invalid response " + String(response, HEX));
    }
    else if (responseStatus == OpenThermResponseStatus::TIMEOUT){
        Serial.println("Error: Response timeout");
    }
    Serial.println("CH Temp set is "+ String(CH_SETPOINT));
    ot.setBoilerTemperature(CH_SETPOINT+2.5f); // poprawka w celu wyrównania spadku cyklicznego
    ot.setDHWSetpoint(40.0f);

    step++;
    if(step % 10 == 0) showStatus();
    if(step >= 1000) step = 0;
    if(sendDataTime >= WAIT){
      getTemperature();
      setBoilerInfo();
      sendDataTime = 0;
    }
  }
  delay(50);
}
