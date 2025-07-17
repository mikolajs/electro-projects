#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define POMP1 1
#define POMP1_TIME 5000
#define POMP2 2
#define POMP2_TIME 5000
//in seconds!!!!
#define HOUR 1
///000000
unsigned long lastWaterTime = 0;
unsigned long aTime = 0;
const long WATER_TIME = 48;
const char* ssid = "sweethome12";
const char* password = "9A0033D4";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

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
  timeClient.begin();
  timeClient.update();
  lastWaterTime = timeClient.getEpochTime();
}

void hoursPeriod(){
  timeClient.update();
  aTime = timeClient.getEpochTime();
}
void mkWater(){
  Serial.println(lastWaterTime);
  Serial.println("Water");
  digitalWrite(POMP1, HIGH);
  delay(POMP1_TIME);
  digitalWrite(POMP1, LOW);
  digitalWrite(POMP2, HIGH);
  delay(POMP2_TIME);
  digitalWrite(POMP2, LOW);

}
void loop() {
  delay(10000);
  hoursPeriod();
  Serial.print("get time: ");
  Serial.println(aTime);
  unsigned long period = aTime - lastWaterTime;
  if(period >= HOUR*WATER_TIME) {
    mkWater();
    lastWaterTime = aTime;
  }
  delay(100);
  //delay(HOUR);
}
