
#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid     = "sweethome12";
const char* password = "9A0033D4";

const int dhtpin = 2;

WiFiServer server(80);

DHT dht(dhtpin, DHT22);
float t = 0;
float h = 0;
int lastCommand = 0;


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
  server.begin();
  dht.begin();
}

void loop() {
    WiFiClient client = server.available();  
    if (client) {                             
    Serial.println("New Client.");          
    String currentLine = ""; 
    String header;        
    while (client.connected()) { // loop while the client's connected
      //currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /") >= 0) {
             client.print("temp=");
             client.print(t);
             client.print("&hum=");
             client.print(h);
             client.println("");         
            } 
            
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  } else {
    
  }
  delay(10);

  //Serial.println(millis() - lastCommand);
  if((millis() - lastCommand) >= 2000){
      lastCommand = millis();
      t = dht.readTemperature();
      h = dht.readHumidity();
    }
}
