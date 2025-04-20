#include <EasyOpenTherm.h>
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define WAIT  180000        /* Time ESP32 will go to sleep (in miliseconds) */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

/*
CH_SETPOINT_BOUNDS to wartość na jaką ustawiłem pokrętło ogrzewania na piecyku 
czyli muszę ustawić pokrętło na jakąś wartość maksymalną a sterować przoprzez CONTROL_CH_SETPOINT
BOILER_WATER_TEMP to temperatura ogrzanej wody w piecyku
RETURN_WATER_TEMP to temperatura po ogrzaniu wracająca z obiegu. Ta interesuje mnie, aby ją ustawić. 
*/

float CH_SETPOINT = 30.0f;
static OpenTherm ot(4, 5);
uint waitingTime = 0;

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

void showStatus(){
  //uint8_t primaryFlags = uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_CH_ENABLE);
  uint8_t primaryFlags = uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_DHW_ENABLE) | uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_CH_ENABLE) | uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_COOLING_ENABLE) | uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_OTC_ENABLE);
  //primaryFlags != uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_CH2_ENABLE);
  //primaryFlags |=  uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_OTC_ENABLE);
  //primaryFlags |=  uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_DHW_ENABLE);  // Enable Domestic Hot Water 
  //primaryFlags |= uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_COOLING_ENABLE);     // Enable cooling (of your boiler, if available) 
  // Send primaryFlags to the boiler to request services. Receive statusFlags from the boiler to see if it is in fault status, if it is in central heating status or domestic hot water, if it's flame is burning, etc.
  Serial.println("Request services from the boiler and check it's status...");
  uint8_t statusFlags;
  if(ot.status(primaryFlags, statusFlags)) {                                                        // Mandatory support
    Serial.printf("Status flags is 0x%02x\n", statusFlags);
    Serial.printf("Set flags is 0x%02x\n", primaryFlags);
    if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_CH_ENABLE)) Serial.println("CH ENABLED");
    if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_DHW_ENABLE)) Serial.println("HOT WATER DHW ENABLED");
    if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::PRIMARY_CH2_ENABLE)) Serial.println("CH2 ENABLED");
      // Show the meaning of each bit in the statusFlags received from the boiler
   //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_FAULT_INDICATION)) Serial.println("FAULT NOTIFICATION");
    //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_CH_MODE)) Serial.println("Central Heating (CH) MODE");
    //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_DHW_MODE)) Serial.println("Domestc Hot Water (DHW) MODE");
    //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_FLAME_STATUS)) Serial.println("Flame is on");
    //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_COOLING_STATUS)) Serial.println("Cooling");
    //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_CH2_MODE)) Serial.println("Second Central Heating system (CH2) is active");
    //if(statusFlags & uint8_t(OpenTherm::STATUS_FLAGS::SECONDARY_DIAGNOSTIC_IND)) Serial.println("DIAGNOSTICS INDICATION");
  } else {
    Serial.println("Failed to get status");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("START");
  connectWifi();
  uint16_t code = 11;
  if(!ot.write(OpenTherm::WRITE_DATA_ID::PRIMARY_CONFIGURATION, code)){
    Serial.println("Primary config error");
  }
  //showStatus();
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
//        if(!ot.write(OpenTherm::WRITE_DATA_ID::DHW_SETPOINT, Temp)) {
//         Serial.printf("Failed to set Central Heating (CH) temperature setpoint to %.01f *C\n", CH_SETPOINT);
//        } else Serial.printf("Sucessly set temp %01f *C\n", Temp);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        if(!ot.write(OpenTherm::WRITE_DATA_ID::CONTROL_SETPOINT_CH, 30.0f)) {
          Serial.printf("Failed to set Central Heating (CH) temperature setpoint to %.01f *C\n", CH_SETPOINT);
        } else Serial.printf("Error HTTTP, set temp 30*C\n");
      }
      // Free resources
      http.end();
      //opdelay(1000);
    } else {
      Serial.println("WiFi Disconnected");
      connectWifi();
    }
}

float readTemperature(){
   float temperatureNow = -100.0f;
   if(ot.read(OpenTherm::READ_DATA_ID::RETURN_WATER_TEMPERATURE,  temperatureNow)){
      Serial.printf("temperature now is %0.01f *C\n", temperatureNow);
    } else {
      Serial.printf("Cannot read temperature\n");
    }
    return temperatureNow;
}

bool runSet(){
  Serial.print("runSet(), SetPoint temperature = ");
  Serial.println(CH_SETPOINT);
  if(!ot.write(OpenTherm::WRITE_DATA_ID::CONTROL_SETPOINT_CH, CH_SETPOINT)) {
     Serial.printf("Failed to set Central Heating (CH) temperature setpoint to %.01f *C\n", CH_SETPOINT);
     return false;
  } else return true;
}

void test(){
  float t = -1.0f;
  //wracająca woda
   if(ot.read(OpenTherm::READ_DATA_ID::RETURN_WATER_TEMPERATURE,  t)) Serial.printf("RETURN WATER TEMP %0.01f\n", t);
   t = -1.0f;
   //temperatura w piecyku
   if(ot.read(OpenTherm::READ_DATA_ID::BOILER_WATER_TEMP,  t)) Serial.printf("BOILER_WATER_TEMP %0.01f\n", t);
   t = -1.0f;
   //usawienie pokrętła ogrzewania   
   if(ot.read(OpenTherm::READ_DATA_ID::CH_SETPOINT_BOUNDS,  t)) Serial.printf("CH_SETPOINT_BOUNDS %0.01f\n", t);
   uint16_t u;
   if(ot.read(OpenTherm::READ_DATA_ID::OEM_DIAGNOSTIC,  u)) Serial.printf("OEM_DIAGNOSTC %d\n", u);  
}

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

void loop() {

  showStatus();
  delay(3000);
  //getTemperature();
  runSet();
  waitingTime += 3000;
  if(waitingTime > WAIT){
    getTemperature();
    setBoilerInfo();
    waitingTime = 0;
  }
  delay(3000);
  waitingTime += 3000;
  //test(); 
}
