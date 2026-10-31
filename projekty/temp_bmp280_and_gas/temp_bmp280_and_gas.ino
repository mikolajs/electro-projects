#include <Wire.h>
#include <BMx280I2C.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <esp_sleep.h>
#define I2C_ADDRESS 0x76
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  180        /* Time ESP32 will go to sleep (in seconds) */
#define GAS 3

//create a BMx280I2C object using the I2C interface with I2C Address 0x76
BMx280I2C bmx280(I2C_ADDRESS);

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

int maxGasMeasure(){
  int gasSensor = 0;
  int maxGas = 0;
  for(int i = 0; i < 5; i++){
    gasSensor = analogRead(GAS);
    if(maxGas < gasSensor) maxGas = gasSensor;
    delay(200);
  }
  Serial.print("Gas max MiCS-5524 sensor:");
  Serial.println(gasSensor);
  return maxGas;
}

void sendData(double t, double h, double p){
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient wifi;
      HTTPClient http;
      String serverPath =  "http://192.168.0.120:8989/measures?th=white_owen&T=";
      serverPath += String(t,2);
      serverPath += "&h=";
      serverPath += String(h, 2);
      serverPath += "&p=";
      serverPath += String(p, 2);
      int g = maxGasMeasure();
      serverPath += "&g=";
      serverPath += String(g);
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
bool measureAndSendData(){
  connectWifi();
  float p = bmx280.getPressure();
  float t = bmx280.getTemperature();
  float h = bmx280.getHumidity();
  Serial.println("t = " + String(t, 2) + " h = " + String(h, 2) + " p = " + String(p, 2) + " Pa");
  sendData(t, h, p);
  
  if(t == NAN || h == NAN) return false;
  else return true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //wait for serial connection to open (only necessary on some boards)
  while (!Serial);
  Wire.begin(0, 1);
  if (!bmx280.begin()){
    Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
    while (1);
  }
}

void loop() {
  if (bmx280.isBME280()) Serial.println("sensor is a BME280");
  else  Serial.println("sensor is a BMP280");
  
  bmx280.resetToDefaults();

	//by default sensing is disabled and must be enabled by setting a non-zero
	//oversampling setting.
	//set an oversampling setting for pressure and temperature measurements. 
	bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
	bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);

	//if sensor is a BME280, set an oversampling setting for humidity measurements.
	if (bmx280.isBME280())
		bmx280.writeOversamplingHumidity(BMx280MI::OSRS_H_x16);
  //reset sensor to default parameters.
  delay(1000);
  if (!bmx280.measure()) {
		Serial.println("could not start measurement, is a measurement already running?");
		return;
	}
	//wait for the measurement to finish
	do {
		delay(100);
	} while (!bmx280.hasValue());
  
  if (measureAndSendData()) delay(TIME_TO_SLEEP*1000);
  else delay(10000);
    
}
