
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

const char* ssid     = "sweethome12";
const char* password = "9A0033D4";
const char* url = "/temp/1";
const char* host = "192.168.0.104:9900";  

const int dhtpin = 2;
DHT dht(dhtpin, DHT22);
float t = 0;
float h = 0;
int lastCommand = 0;


bool sendTemp(){
  WiFiClient client;
  //client.setInsecure(); //the magic line, use with caution
  if(!client.connect(host, 80)) {
  	Serial.println("Host not found!");
  	return false;
  }
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "User-Agent: termometerPoint1\r\n" +
             "Connection: close\r\n\r\n");
  client.print("t=");
  client.print(t);
  client.print("&h=");
  client.print(h);
 while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  return true;
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
   int i = 3;
   while(i--){
     delay(200);
     if(sendTemp()) break;
     else {
       Serial.print("Cannot open server");
       Serial.println();
     }
  }
  delay(100);
  //Serial.println(millis() - lastCommand);
  if((millis() - lastCommand) >= 2000){
      lastCommand = millis();
      t = dht.readTemperature();
      h = dht.readHumidity();
    }
    ESP.deepSleep(60000000); 
}
