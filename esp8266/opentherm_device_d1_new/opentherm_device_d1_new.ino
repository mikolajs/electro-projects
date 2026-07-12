#include <OpenTherm.h>
// #define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define WAIT  180000        /* Time ESP32 will go to sleep (in miliseconds) */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
/*
CH_SETPOINT_BOUNDS to wartość na jaką ustawiłem pokrętło ogrzewania na piecyku 
czyli muszę ustawić pokrętło na jakąś wartość maksymalną a sterować przoprzez CONTROL_CH_SETPOINT
BOILER_WATER_TEMP to temperatura ogrzanej wody w piecyku
RETURN_WATER_TEMP to temperatura po ogrzaniu wracająca z obiegu. Ta interesuje mnie, aby ją ustawić. 
*/
///Włącza się co chwila i ustawia za dużą temperaturę!!!
float CH_SETPOINT = 30.0f;
//podłączenie kabli: czerwony -    , zielony -
static OpenTherm ot(4, 5);
uint waitingTime = 0;
const int step = 15000;


void ICACHE_RAM_ATTR handleInterrupt(){
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

void setup()
{
	Serial.begin(115200);
	Serial.println("Start");
	
	ot.begin(handleInterrupt);
  connectWifi();
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
        CH_SETPOINT = Temp;
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        CH_SETPOINT = 30.0f;
        Serial.printf("Failed to set Central Heating (CH) temperature setpoint to %.01f *C\n", CH_SETPOINT);
      }
      // Free resources
      http.end();
      //opdelay(1000);
    } else {
      Serial.println("WiFi Disconnected");
      connectWifi();
    }
}

/*
void setBoilerInfo(){
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/addboilerinfo?rwt=";
      float t = -1.0f;
       //wracająca woda
      if(ot.read(OpenTherm::READ_DATA_ID::RETURN_WATER_TEMPERATURE,  t)) Serial.printf("RETURN WATER TEMP %0.01f\n", t);
      serverPath += String(t);
      t = -1.0f;
       //temperatura w piecyku
      if(ot.read(OpenTherm::READ_DATA_ID::BOILER_WATER_TEMP,  t)) Serial.printf("BOILER_WATER_TEMP %0.01f\n", t);
      serverPath += "&bwt=";
      serverPath += String(t);
      t = -1.0f;
       //usawienie pokrętła ogrzewania   
      if(ot.read(OpenTherm::READ_DATA_ID::CH_SETPOINT_BOUNDS,  t)) Serial.printf("CH_SETPOINT_BOUNDS %0.01f\n", t);
      serverPath += "&spb=";
      serverPath += String(t);
      uint16_t u;
      if(ot.read(OpenTherm::READ_DATA_ID::OEM_DIAGNOSTIC,  u)) Serial.printf("OEM_DIAGNOSTC %d\n", u);
      serverPath += "&oemd=";
      serverPath += String(u);
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
*/

void printInfo(){
  Serial.println("CH_Setpoint: " + String(CH_SETPOINT));
  Serial.println("Temp: " + String(ot.getBoilerTemperature()));
  Serial.println("Return temp: " + String(ot.getReturnTemperature()));
  Serial.println("DHWT temp: " + String(ot.getDHWTemperature()));
}
void loop() {
	
  unsigned long response = ot.setBoilerStatus(true, true, false);
  OpenThermResponseStatus responseStatus = ot.getLastResponseStatus();
  if (responseStatus == OpenThermResponseStatus::SUCCESS){
        Serial.println("Central Heating: " + String(ot.isCentralHeatingActive(response) ? "on" : "off"));
        Serial.println("Hot Water: " + String(ot.isHotWaterActive(response) ? "on" : "off"));
        Serial.println("Flame: " + String(ot.isFlameOn(response) ? "on" : "off"));
  }
  if (responseStatus == OpenThermResponseStatus::NONE){
        Serial.println("Error: OpenTherm is not initialized");
  } else if (responseStatus == OpenThermResponseStatus::INVALID){
        Serial.println("Error: Invalid response " + String(response, HEX));
  } else if (responseStatus == OpenThermResponseStatus::TIMEOUT){
        Serial.println("Error: Response timeout");
  }
  ot.setBoilerTemperature(CH_SETPOINT);
  printInfo();
  if(waitingTime > WAIT){
    // getTemperature();
    // setBoilerInfo();
    // waitingTime = 0;
  }
  delay(step);
  waitingTime += step;
  //test(); 
}
