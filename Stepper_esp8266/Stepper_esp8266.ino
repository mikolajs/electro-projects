//#include <Servo.h>
#include <ESP8266WiFi.h>


const int STEP_1 = 5;
const int STEP_2 = 4;
const int STEP_3 = 0;
const int STEP_4 = 2;

int move = 0; // -1 down 1 up 0 stop


const int WAIT = 2;

WiFiServer server(80);

long lastCommand = 0;
long currentTime;
long previousTime;
long timeoutTime = 2000;
String header;

void setup(){
  pinMode(STEP_1, OUTPUT);
  pinMode(STEP_2, OUTPUT);
  pinMode(STEP_3, OUTPUT);
  pinMode(STEP_4, OUTPUT);
   Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("MiniAutko01", "12345678");
  Serial.println("WIFI IP address");
  Serial.println(WiFi.localIP());
  server.begin();
}

void stepDown(){
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, HIGH);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, HIGH);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, HIGH);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, HIGH);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
}

void stepUp(){
  digitalWrite(STEP_1, HIGH);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, HIGH);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, HIGH);
  digitalWrite(STEP_4, LOW);
  delay(WAIT);
  digitalWrite(STEP_1, LOW);
  digitalWrite(STEP_2, LOW);
  digitalWrite(STEP_3, LOW);
  digitalWrite(STEP_4, HIGH);
  delay(WAIT);
}

void mkMove(){
  switch(move){
    case -1: 
      stepUp();
      break;
    case 1: 
      stepDown();
      break;
    default:
      break;
  }
}


void loop() {
    WiFiClient client = server.available(); 
    
      mkMove();
    
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
              move = 1;
            } else if (header.indexOf("GET /command/b") >= 0) {
              Serial.println("BACKWARD");
              move = -1;
            } else if(header.indexOf("GET /command/s") >= 0) {
              Serial.println("STOP");
              move = 0;
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
            client.println("<p><a href=\"/command/f\"><button class=\"button\">UP</button></a></p>");
            client.println("<p><a href=\"/command/b\"><button class=\"button\">DOWN</button></a></p>");
             
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
