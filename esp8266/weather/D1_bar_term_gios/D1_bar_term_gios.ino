
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include "BMP280lib.h"



const char* ssid     = "itechwoman";
const char* password = "myK0biety";

const int dhtpin = 2;

WiFiServer server(80);


DHT dht(dhtpin, DHT22);
//D1  i D2
BMx280SoftWire bmx280(I2C_ADDRESS);
float t = 0;
float h = 0;
float p = 0;
String a = "brak danych";
int lastCommand = 0;
String giosInfoJSON;
String giosInfo;


void indexContent(WiFiClient& client){
  client.println("<!DOCTYPE html>");
client.println("<html lang='en' dir='ltr'>");
client.println("<head>");
client.println("<meta charset='utf-8'>");
client.println("<style media='screen'>");
client.println(".aBox {");
client.println("border: solid 2px black; margin: 4%;   text-align: center; width: 40%;");
client.println("vertical-align: middle; display: inline-block; border-radius: 10px; align-items: center;");
client.println("}");
client.println(".c1 {background-color: SlateBlue;  height: 100px;}");
client.println(".c2 {background-color: Tomato; height: 100px;}");
client.println(".c3 {background-color: MediumSeaGreen; height: 100px;}");
client.println(".c4 {background-color: Gold; height: 100px;}");
client.println(".innerText {  position: relative; margin: auto; font-size: 2em; color: white; top: 30%;}");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<div class='main'>");
client.println("<div class='aBox c1'>");
client.println("<span class='innerText'>Temperatura: </span>");
client.print("<span id='temp' class='innerText'>");
client.print(t);
client.println("°C</span>");
client.println("</div>");
client.println("<div class='aBox c2'>");
client.println("<span class='innerText'>Wilgotność: </span>");
client.print("<span id='wilg' class='innerText'>");
client.print(h);
client.println("%</span>");
client.println("</div>");
client.println("<div class='aBox c3'>");
client.println("<span class='innerText'>Ciśnienie: </span>");
client.print("<span id='cis' class='innerText'>");
client.print(p);
client.println("hPa</span>");
client.println("</div>");
client.println("<div class='aBox c4'>");
client.println("<span class='innerText'>Stan powietrza:</span>");
client.print("<span id='pow' class='innerText'>");
client.println("</span>");
client.println("</div>");
client.println("<textarea id='gios' style='display:none;'>");
client.println(giosInfoJSON);
client.println("</textarea>");
client.println("</div>");
client.println("<script type='text/javascript'>");
client.println("let json = JSON.parse(document.getElementById('gios').value);");
client.println("console.log(json.stIndexLevel.indexLevelName);");
client.println("document.getElementById('pow').innerHTML = json.stIndexLevel.indexLevelName;");
client.println("</script>");
client.println("</body>");
client.println("</html>");
}

void getAirDirectly(){
  const char* url = "/pjp-api/rest/aqindex/getIndex/736";
  const char* host = "api.gios.gov.pl";   
  giosInfoJSON = "";  
  WiFiClient client;
  //client.setInsecure(); //the magic line, use with caution
  if(!client.connect(host, 80)) Serial.println("Not connected to GIOS host");
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:99.0) Gecko/20100101 Firefox/99.0\r\n" +
             "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n" + 
             "Accept-Language: pl,en-US;q=0.7,en;q=0.3\r\n" +
             "Connection: keep-alive\r\n\r\n");
  String headersGIOS = "";
  bool endHeaders = false;
 while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      endHeaders = true;
      Serial.println("Headers received");
    } else if(endHeaders) {
      giosInfo = line;
      break;
    } else Serial.println(line);
  }
  giosInfoJSON  = client.readStringUntil('\n');
  Serial.println(giosInfoJSON);
  client.stop();
}

void getAir(){
  const char* url = "/get/736";
  const char* host = "localhost:8008";   
  giosInfo = "";  
  WiFiClient client;
  //client.setInsecure(); //the magic line, use with caution
  if(!client.connect(host, 80)) Serial.println("Not connected to GIOS host");
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "User-Agent: BuildFailureDetectorESP8266\r\n" +
             "Connection: close\r\n\r\n");
 while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  giosInfo = client.readStringUntil('\n');
  client.stop();
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
  //start server http
  server.begin();
  //start DHT22
  dht.begin();
  
  //BMP280 setup
  sw.setDelay_us(5);
  sw.setTimeout_ms(100);
  sw.begin();

  //begin() checks the Interface, reads the sensor ID (to differentiate between BMP280 and BME280)
  //and reads compensation parameters.
  if (!bmx280.begin())
  {
    Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
    while (1);
  }

  //reset sensor to default parameters.
  bmx280.resetToDefaults();

  //by default sensing is disabled and must be enabled by setting a non-zero
  //oversampling setting.
  //set an oversampling setting for pressure and temperature measurements. 
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);
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
            client.println("Access-Control-Allow-Origin:*");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
           /* if (header.indexOf("GET /get") >= 0) {
             client.print("t=");
             client.print(t);
             client.print("&h=");
             client.print(h);
             client.print("&p=");
             client.print(p);
             client.print("&a=");
             getAir();
             client.print(giosInfo);
             
             client.println("");         
            } else if(header.indexOf("GET /") >= 0){ */
              getAirDirectly();
              indexContent(client);
           // }
            
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
    //Serial.print(".");
  }
  delay(10);

  //Serial.println(millis() - lastCommand);
  if((millis() - lastCommand) >= 2000){
      lastCommand = millis();
      t = dht.readTemperature();
      h = dht.readHumidity();
      //Serial.print("temperatura = ");
      //Serial.println(t);
      //Serial.print("wilgotność = ");
      //Serial.println(h);
      if(bmx280.measure()){
       int checks = 0;
       do { delay(50); checks++; if(checks > 10) break; }
       while(!bmx280.hasValue());
        p = bmx280.getPressure();
        p /= 100;
        //Serial.print("Temperatura BMP280 = "); Serial.println(bmx280.getTemperature());
      }
      //Serial.print("ciśnienie =");
      //Serial.println(p);
    }
}
