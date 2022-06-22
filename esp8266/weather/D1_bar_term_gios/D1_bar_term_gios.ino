
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>



const char* ssid     = "sweethome12";
const char* password = "9A0033D4";

const int dhtpin = 2;

WiFiServer server(80);


DHT dht(dhtpin, DHT22);
Adafruit_BMP280 bmp;
float t = 0;
float h = 0;
float p = 0;
int lastCommand = 0;
String giosInfo;


void indexContent(WiFiClient& client){
  client.println("<!DOCTYPE html>");
client.println("<html lang='en' dir='ltr'>");
client.println("<head>");
client.println("<meta charset='utf-8'>");
client.println("<style media='screen'>");
client.println(".aBox {");
client.println("border: solid 2px black; margin: 4%;   text-align: center;");
client.println("vertical-align: middle; display: inline-block; border-radius: 10px; align-items: center;");
client.println("}");
client.println(".c1 {background-color: SlateBlue; width: 40%; height: 100px;}");
client.println(".c2 {background-color: Tomato; width: 40%; height: 100px;}");
client.println(".c3 {background-color: MediumSeaGreen;  width: 90%; min-height: 100px;}");
client.println(".innerText {  position: relative; margin: auto; font-size: 2em; color: white; top: 30%;}");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<div class='main'>");
client.println("<div class='aBox c1'>");
client.println("<span class='innerText'>Temperatura: </span>");
client.println("<span id='temp' class='innerText'>???</span>");
client.println("</div>");
client.println("<div class='aBox c2'>");
client.println("<span class='innerText'>Wilgotność: </span>");
client.println("<span id='wilg' class='innerText'>???</span>");
client.println("</div>");
client.println("<div class='aBox c3'>");
client.println("<span class='innerText'>Stan powietrza:</span>");
client.println("<span id='pow' class='innerText'>???</span>");
client.println("");
client.println("</div>");
client.println("</div>");
client.println("<script type='text/javascript'>");
client.println("let T;");
client.println("let H;");
client.println("let A;");
client.println("let aInfo;");
client.println("let req = new XMLHttpRequest();");
client.println("let req2 = new XMLHttpRequest();");
client.println("req.open('GET', 'http://192.168.0.142/get', true);");
client.println("req.onreadystatechange = addDataAndFindAir;");
client.println("req.send(null);");
client.println("function addDataAndFindAir(e){");
client.println("if (req.readyState == 4) {");
client.println("if(req.status == 200) {");
client.println("let text = req.responseText;");
client.println("console.log(text);");
client.println("text.trim().split('&').forEach((item) => {");
client.println("let a = item.split('=');");
client.println("if(a.length > 1 && a[0] == 't') T = a[1];");
client.println("else if(a.length > 1 && a[0] == 'h') H = a[1];");
client.println("if(a.length > 1 && a[0] == 'a') A = parseInt(a[1]);");
client.println("});");
client.println("document.getElementById('temp').innerText = T + '°';");
client.println("document.getElementById('wilg').innerText = H + '%';");
client.println("req2.open('GET', 'https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/'+A, true);");
client.println("req2.onreadystatechange = findAir;");
client.println("req2.send(null);");
client.println("}");
client.println("else console.log('Błąd podczas ładowania strony');");
client.println("}");
client.println("}");
client.println("function findAir(e){");
client.println("if (req2.readyState == 4) {");
client.println("if(req2.status == 200) {");
client.println("let json = JSON.parse(req2.responseText);");
client.println("console.log(json.stIndexLevel.indexLevelName);");
client.println("}");
client.println("else console.log('Błąd podczas ładowania strony');");
client.println("}");
client.println("}");
client.println("</script>");
client.println("</body>");
client.println("</html>");

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
  server.begin();
  dht.begin();
  if (!bmp.begin()) {  
   Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
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
            if (header.indexOf("GET /get") >= 0) {
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
            } else if(header.indexOf("GET /") >= 0){
              indexContent(client);
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
  delay(100);

  //Serial.println(millis() - lastCommand);
  if((millis() - lastCommand) >= 2000){
      lastCommand = millis();
      t = dht.readTemperature();
      h = dht.readHumidity();
      Serial.println(t);
      Serial.println(h);
      p = bmp.readPressure();
      Serial.println(p);
    }
}
