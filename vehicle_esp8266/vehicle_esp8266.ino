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
#include <Servo.h>

const char *ssid = "fablabauto1"; // SSID Name
const char *password = "12345678"; // SSID Password : Between 8 and 32 carateres

IPAddress ip(192, 168, 4, 1); // IP Address
IPAddress netmask(255, 255, 255, 0); // Netmask
const int port = 80; // Port
ESP8266WebServer server(port);

// Motors pins
static const uint8_t motor_r = 0 ;
static const uint8_t motor_l = 5;
Servo servo_r;
Servo servo_l;

void setup() {
  WiFi.mode(WIFI_AP); //Only Access point
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);
  servo_r.attach(motor_r);
  servo_r.attach(motor_l);
  // Start Server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {
   servo_r.write(-360);
  servo_l.write(-360);
  delay(1000);                                                                                                                                                                                                                                                                                          
  //server.handleClient();
}

void handleRoot() {
  if (server.hasArg("State")) {
    String command = server.arg("State");
    if (command.equals("F")) {
      forward();
      server.send(200, "text / plain", "Forward");
    }
    else  if (command.equals("B")) {
      backward();
      server.send(200, "text / plain", "Backward");
    }
    else  if (command.equals("L")) {
      turn_left();
      server.send(200, "text / plain", "Turn Left");
    }
    else  if (command.equals("R")) {
      turn_right();
      server.send(200, "text / plain", "Turn Right");
    }
    else  if (command.equals("S")) {
      stop_motors();
      server.send(200, "text / plain", "Stop");
    }
  }
}

void stop_motors() {
  servo_r.write(90);
  servo_l.write(90);
}

void backward() {
  servo_r.write(-360);
  servo_l.write(-360);
}

void forward() {
  servo_r.write(360);
  servo_l.write(360);
}

void turn_left() {
  servo_r.write(360);
  servo_l.write(-360);
}

void turn_right() {
  servo_r.write(-360);
  servo_l.write(360);
}
