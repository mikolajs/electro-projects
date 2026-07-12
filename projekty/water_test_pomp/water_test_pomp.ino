#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  20 

#define POMP1 23
#define POMP1_TIME 9000
RTC_DATA_ATTR int bootCount = 0;


void mkWater() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(POMP1, HIGH);
    delay(POMP1_TIME);
    //aTime += 2*POMP1_TIME;
    digitalWrite(POMP1, LOW);
    delay(POMP1_TIME);
  }
}


void setup() {
  pinMode(POMP1, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  while(!Serial){}
  ++bootCount;
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  Serial.println("Boot count: " + String(bootCount));
  digitalWrite(POMP1, LOW);
  
  // Serial.println("");
  Serial.println("WiFi connected");
  delay(1000);
  mkWater();
  digitalWrite(POMP1, LOW);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.print("Go to sleep for ");
  Serial.println(String(TIME_TO_SLEEP * uS_TO_S_FACTOR));
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
}
