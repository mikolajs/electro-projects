/**
  @brief   Simple example of Wifi Car controlled by a web server in AP Mode. See also :
           http://www.instructables.com/id/A-very-cheap-ESP8266-WiFi-smart-car-controlled-by-/
           List of commands to control the car :
           - http://<YourIP>:<YourPort>/?State=F (Forward)
           - http://<YourIP>:<YourPort>/?State=B (Backward)
           - http://<YourIP>:<YourPort>/?State=R (TurnRight)
           - http://<YourIP>:<YourPort>/?State=L (TurnLeft)
           - http://<YourIP>:<YourPort>/?State=S (Stop)
  @author  LACOUR Vincent
  @changes Mikolaj Sochacki – using servo 360 degree    
  @date    2018-01 end 2019-10-03  
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "fablabauto1"; // SSID Name
const char *password = "12345678"; // SSID Password : Between 8 and 32 carateres

IPAddress ip(192, 168, 4, 1); // IP Address
IPAddress netmask(255, 255, 255, 0); // Netmask
const int port = 80; // Port
ESP8266WebServer server(port);

// Motors pins
static const uint8_t motor_r = 0 ;
static const uint8_t motor_l = 5;

void setup() {
  WiFi.mode(WIFI_AP); //Only Access point
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);
  // Start Server
  server.on("/command", HTTP_GET, handleCommand);
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {

  delay(1000);                                                                                                                                                                                                                                                                                          
  //server.handleClient();
}

void handleRoot(){
  server.send(200, "text / plain", "Server Arduino");
}

void handleCommand() {
  if (server.hasArg("State")) {
    String command = server.arg("State");
    if (command.equals("F")) {
      forward();
      server.send(200, "text / plain", "Forward");
      Serial.println("Forward");
    }
    else  if (command.equals("B")) {
      backward();
      server.send(200, "text / plain", "Backward");
        Serial.println("Backward");
    }
    else  if (command.equals("L")) {
      turn_left();
      server.send(200, "text / plain", "Turn Left");
        Serial.println("Left");
    }
    else  if (command.equals("R")) {
      turn_right();
      server.send(200, "text / plain", "Turn Right");
        Serial.println("Rigth");
    }
    else  if (command.equals("S")) {
      stop_motors();
      server.send(200, "text / plain", "Stop");
        Serial.println("Stop");
    }
  }
}

void stop_motors() {
  
}

void backward() {
 
}

void forward() {
 
}

void turn_left() {
  
}

void turn_right() {
  
}
