#include <Servo.h>
#include <ESP8266WiFi.h>


const int leftF = -1;
const int rightF = 1; 
const int pinL = 4;
const int pinR = 5;

WiFiServer server(80);


long lastCommand = 0;
long currentTime;
long previousTime;
long timeoutTime = 2000;
String header;
//bool stopedL = true;
//bool stopedR = true;

Servo servoLeft;
Servo servoRight;

/*void stopR(){
  if(!stopedR) {
    Serial.println("stopR");
    servoRight.detach();
    stopedR = true;
  }
}

void stopL(){
  if(!stopedL) {
    Serial.println("stopL");
    servoLeft.detach();
    stopedL = true;
  }
}
*/

void moveR(){
  servoLeft.write(90);
  servoRight.write(360*rightF);
  lastCommand = millis(); 
}

void moveL(){
  servoRight.write(90);
  servoLeft.write(360*leftF);
  lastCommand = millis();  
}

void moveF(){
  servoLeft.write(360*leftF); 
  servoRight.write(360*rightF); 
  lastCommand = millis(); 
}

void moveB(){
  servoLeft.write(-360*leftF); 
  servoRight.write(-360*rightF); 
  lastCommand = millis(); 
}

void stopAll(){
 servoLeft.write(90);
 servoRight.write(90);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("MiniAutko01", "12345678");
  Serial.println("WIFI IP address");
  Serial.println(WiFi.localIP());
  server.begin();
}

void showPage(WifiClient& client){
	client.println("<!DOCTYPE html><html> <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
        client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #17ae0A;} .button3 {background-color: #E3070A;}");
            client.println(".slider {   -webkit-appearance: none; width: 80%;height: 25px; background: #d3d3d3;outline: none;opacity: 0.7;");
              client.println("-webkit-transition: .2s;transition: opacity .2s;}");
            client.println(".slider::-webkit-slider-thumb {-webkit-appearance: none;appearance: none;width: 25px;height: 25px;");
             client.println("background: #4CAF50;cursor: pointer;}");
           client.println(".slider::-moz-range-thumb {width: 25px; height: 25px;background: #4CAF50;cursor: pointer;}  </style>");
            client.println("<script>function command(l){var client = new XMLHttpRequest();client.open('GET', '/command/' + l);client.send(null);}</script>");
          client.println("</head><body><p><button onclick=\"command('a');\" class=\"button\">a</button>");
              client.println("<button class=\"button button2\" onclick=\"command('f');\">&#8593; <small>f</small></button>");
              client.println("<button class=\"button\" onclick=\"command('u');\">u</button></p>");
            client.println("<p><button class=\"button button2\" onclick=\"command('l');\">&#8592; <small>l</small></button>");
             client.println("<button class=\"button button3\" onclick=\"command('x');\">x</button>");
            client.println("<button class=\"button button2\" onclick=\"command('r');\">&#8594; <small>r</small></button></p>");
            client.println("<p><button class=\"button\" onclick=\"command('d');\">d</button></a>");
             client.println("<button class=\"button button2\" onclick=\"command('b');\">&#8595; <small>b</small></button>");
             client.println("<button class=\"button\" onclick=\"command('c');\">c</button> </p>");
             client.println("<p><input type=\"range\" min=\"0\" max=\"8\" value=\"4\"  onchange=\"command(this.value)\" class=\"slider\" id=\"myRange\"></p>");
            client.println("</body></html>");
}

char getCommand(String h){
 // turns the GPIOs on and off
            if (header.indexOf("GET /command/f") >= 0) {
              Serial.println("f");
              return 'f'
            } else if (header.indexOf("GET /command/b") >= 0) {
              Serial.println("b");
              return 'b';
            } else if (header.indexOf("GET /command/r") >= 0) {
              Serial.println("r");
              return 'r';
            } else if (header.indexOf("GET /command/l") >= 0) {
              Serial.println("l");
              return 'l';
            } else if (header.indexOf("GET /command/x") >= 0) {
              Serial.println("x");
              return 'x';
            } else if (header.indexOf("GET /command/a") >= 0) {
              Serial.println("a");
              return 'a';
            } else if (header.indexOf("GET /command/u") >= 0) {
              Serial.println("u");
              return 'u';
            } else if (header.indexOf("GET /command/d") >= 0) {
              Serial.println("d");
              return 'd';
            } else if (header.indexOf("GET /command/c") >= 0) {
              Serial.println("c");
              return 'c';
            } else if (header.indexOf("GET /command/0") >= 0) {
              Serial.println("0");
              return '0';
            } else if (header.indexOf("GET /command/1") >= 0) {
              Serial.println("1");
              return '1';
            } else if (header.indexOf("GET /command/2") >= 0) {
              Serial.println("2");
              return '2';
            } else if (header.indexOf("GET /command/3") >= 0) {
              Serial.println("3");
              return '3';
            } else if (header.indexOf("GET /command/4") >= 0) {
              Serial.println("4");
              return '4';
            } else if (header.indexOf("GET /command/5") >= 0) {
              Serial.println("5");
              return '5';
            } else if (header.indexOf("GET /command/6") >= 0) {
              Serial.println("6");
              return '6';
            } else if (header.indexOf("GET /command/7") >= 0) {
              Serial.println("7");
              return '7';
            } else if (header.indexOf("GET /command/8") >= 0) {
              Serial.println("8");
              return '8';
            } else return '-';
}

void loop() {
    WiFiClient client = server.available();  
    servoLeft.attach(pinL);
    servoRight.attach(pinR);
//    servoLeft.write(360);
//    servoRight.write(360);
//    delay(5000); 
//    servoLeft.write(-360);
//    servoRight.write(-360);
//    delay(5000);
//    Serial.println("WIFI IP address");
//    Serial.println(WiFi.localIP());
    if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";         
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
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
            if (header.indexOf("GET /command/f") >= 0) {
              Serial.println("FORWARD");
              moveF();
            } else if (header.indexOf("GET /command/b") >= 0) {
              Serial.println("BACKWARD");
              moveB();
            } else if (header.indexOf("GET /command/r") >= 0) {
              Serial.println("RIGHT");
              moveR();
            } else if (header.indexOf("GET /command/l") >= 0) {
              Serial.println("LEFT");
              moveL();
            } else if (header.indexOf("GET /command/s") >= 0) {
              Serial.println("STOP");
              stopAll();
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p><a href=\"/command/f\"><button class=\"button\">Forward</button></a></p>");
            client.println("<p><a href=\"/command/l\"><button class=\"button\">Left</button></a>");
            client.println("<a href=\"/command/r\"><button class=\"button\">Right</button></a></p>");
            client.println("<p><a href=\"/command/b\"><button class=\"button\">Backward</button></a></p>");
             
            client.println("<p><a href=\"/command/s\"><button class=\"button\">STOP</button></a></p>");
           
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
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
//  Serial.print("TIME AFTER last command: ");
//  Serial.println(millis() - lastCommand);
//  Serial.println(stopedL);
//  Serial.println(stopedR);
//  if( (millis() - lastCommand) >= 2000){
//      Serial.println("stop");
//      stopAll();
//    }
}
