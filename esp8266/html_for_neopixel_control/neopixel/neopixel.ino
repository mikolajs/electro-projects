#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#define PIN            2
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN,
NEO_GRB + NEO_KHZ800);

char lastCommand = ' ';

WiFiServer server(80);

long lastCommandTime = 0;
long currentTime;
long previousTime;
long timeoutTime = 2000;
String header;
//bool stopedL = true;
//bool stopedR = true;

int animation = 1;

void showPage(WiFiClient& client);
void makeAnimation();


void setup() {
  Serial.begin(115200);
  /*
  WiFi.begin("network-name", "pass-to-network");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  */
  WiFi.mode(WIFI_AP);
  WiFi.softAP("MiniAutko03", "12345678");
  Serial.println("WIFI IP address");
  Serial.println(WiFi.localIP());
  server.begin();
  pixels.begin();
  randomSeed(analogRead(0));
}

void off() {
  for (int i = 0; i < NUMPIXELS; i++) {
    switchOff(i);
  }
}

void setColor(uint8_t nr, uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(nr, pixels.Color(r, g, b));
  pixels.show();
}

void setRed(int nr, uint8_t pow) {
  setColor(nr, pow, 0, 0);
}

void setGreen(int nr, uint8_t pow) {
  setColor(nr, 0, pow, 0);
}

void setBlue(int nr, uint8_t pow) {
  setColor(nr, 0, 0, pow);
}

void setYellow(int nr, uint8_t pow) {
  setColor(nr, pow, pow, 0);
}

void setViolet(int nr, uint8_t pow) {
  setColor(nr, pow, 0, pow);
}

void setMarine(int nr, uint8_t pow) {
  setColor(nr, 0, pow, pow);
}

void setOrange(int nr, uint8_t pow) {
  uint8_t g = pow * 2 / 3;
  setColor(nr, pow, g, 0);
}

void switchOff(int nr) {
  setColor(nr, 0, 0, 0);
}

void lightDark() {
  for (uint8_t p = 1; p < 250; p += 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 4 == 0)
        setRed(i, p);
      else if (i % 4 == 1)
        setBlue(i, p);
      else if (i % 4 == 2)
        setGreen(i, p);
      else if (i % 4 == 3)
        setYellow(i, p);
    }
    delay(100);
  }
}

void rondo() {
  uint8_t p = 120;
  for (int b = 0; b < 32; b++) {
    int nr = b % NUMPIXELS;
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 4 == 0)
        setRed((i + nr) % NUMPIXELS, p);
      else if (i % 4 == 1)
        setBlue((i + nr) % NUMPIXELS, p);
      else if (i % 4 == 2)
        setGreen((i + nr) % NUMPIXELS, p);
      else if (i % 4 == 3)
        setYellow((i + nr) % NUMPIXELS, p);
    }
    delay(500);
  }
}

void colorLight() {
  uint8_t pow = 120;
  for (int i = 0; i < NUMPIXELS; i++) {
    setRed(i, pow);
  }
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    setGreen(i, pow);
  }
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    setYellow(i, pow);
  }
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    setBlue(i, pow);
  }
  delay(1000);
}

boolean snakeIfOnLed(int i, uint8_t start, uint8_t end, uint8_t N) {
  if (i >= start) {
    if (i < start + N)
      return true;
    else
      return false;
  } else {
    if (end < start) {
      if (i < end)
        return true;
      else
        return false;
    } else
      return false;
  }
  return true;
}

void snakeMove() {
  uint8_t pow = 120;
  uint8_t NUMB = 10;
  uint8_t start = 0;
  uint8_t end = NUMB;
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  for (int k = 1; k < 7; k++) {
    if ((k & 1) > 0)
      r = pow;
    else
      r = 0;
    if ((k & 2) > 0)
      g = pow;
    else
      g = 0;
    if ((k & 4) > 0)
      b = pow;
    else
      b = 0;
    for (int j = 0; j < 64; j++) {
      end = (start + NUMB) % NUMPIXELS;
      for (int i = 0; i < NUMPIXELS; i++) {
        if (snakeIfOnLed(i, start, end, NUMB))
          setColor(i, r, g, b);
        else
          switchOff(i);
      }
      start++;
      start %= NUMPIXELS;
      delay(50);
    }
  }
}

void snakeMoveColor() {
  uint8_t pow = 120;
  uint8_t NUMB = 8;
  uint8_t start = 0;
  uint8_t end = NUMB;
  uint8_t pos = 0;
  for (int j = 0; j < 320; j++) {
    end = (start + NUMB) % NUMPIXELS;
    for (int i = 0; i < NUMPIXELS; i++) {
      if (snakeIfOnLed(i, start, end, NUMB)) {
        if (i >= start)
          pos = i - start;
        else
          pos = i + NUMPIXELS - start;
        switch (pos) {
        case 0:
          setRed(i, pow);
          break;
        case 2:
          setOrange(i, pow);
          break;
        case 3:
          setYellow(i, pow);
          break;
        case 4:
          setViolet(i, pow);
          break;
        case 5:
          setGreen(i, pow);
          break;
        case 6:
          setMarine(i, pow);
          break;
        case 7:
          setBlue(i, pow);
          break;
        default:
          setColor(i, pow, pow, pow);
          break;
        }
      } else
        switchOff(i);
    }
    start++;
    start %= NUMPIXELS;
    delay(50);
  }
}

void randomColor() {
  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      setColor(i, random(120), random(120), random(120));
    }
    delay(1000);
  }
}

void showPage(WiFiClient& client){
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en' dir='ltr'>");
  client.println("<head>");
  client.println("<meta charset='utf-8'>");
  client.println("<script type='text/javascript'>");
  client.println("function runjs(id){");
  client.println("let client = new XMLHttpRequest();");
  client.println("client.open('GET', '/command/' + id.toString());");
  client.println("client.send(null);}");
  client.println("</script>");
  client.println("<style media='screen'>");
  client.println(".aBox {");
  client.println("width: 40%; border: solid 2px black; margin: 4%; height: 100px;  text-align: center;");
  client.println("vertical-align: middle; display: inline-block; border-radius: 10px; align-items: center;");
  client.println("}");
  client.println(".c1 {background-color: SlateBlue; }");
  client.println(".c2 {background-color: Tomato; }");
  client.println(".c3 {background-color: MediumSeaGreen; }");
  client.println(".c4 {background-color: Violet; }");
  client.println(".c5 {background-color: Orange; }");
  client.println(".c6 {background-color: DodgerBlue; }");
  client.println(".innerText {  position: relative; margin: auto; font-size: 2em; color: white; top: 30%;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class='main'>");
  client.println("<div class='aBox c1' onclick='runjs(1)'>");
  client.println("<span class='innerText'>Animacja 1</span>");
  client.println("</div>");
  client.println("<div class='aBox c2' onclick='runjs(2)'>");
  client.println("<span class='innerText'>Animacja 2</span>");
  client.println("</div>");
  client.println("<div class='aBox c3' onclick='runjs(3)'>");
  client.println("<span class='innerText'>Animacja 3</span>");
  client.println("</div>");
  client.println("<div class='aBox c4' onclick='runjs(4)'>");
  client.println("<span class='innerText'>Animacja 4</span>");
  client.println("</div>");
  client.println("<div class='aBox c5' onclick='runjs(5)'>");
  client.println("<span class='innerText'>Animacja 5</span>");
  client.println("</div>");
  client.println("<div class='aBox c6' onclick='runjs(6)'>");
  client.println("<span class='innerText'>Animacja 6</span>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
}

char getCommand(String header){
 // turns the GPIOs on and off
	    if(header.length() < 14) return 'i';
            if (header.indexOf("GET /command/1") >= 0) {
              animation = 1;
              Serial.println("1");
            } else if (header.indexOf("GET /command/2") >= 0) {
              animation = 2;
              Serial.println("2");
            } else if (header.indexOf("GET /command/3") >= 0) {
              animation = 3;
              Serial.println("3");
            } else if (header.indexOf("GET /command/4") >= 0) {
              animation = 4;
              Serial.println("4");
            } else if (header.indexOf("GET /command/5") >= 0) {
              animation = 5;
              Serial.println("5");
            } else if (header.indexOf("GET /command/6") >= 0) {
              animation = 6;
              Serial.println("6");
            } else return 'i';
            return 'a';
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
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


            char c = getCommand(header);

            if(c == 'i') showPage(client);
            else {
              switch(animation){
                case 1:
                  off();
                  snakeMoveColor();
                 break;
                case 2:
                 off();
                 snakeMove();
                 break;
                case 3:
                 off();
                 lightDark();;
                 break;
                case 4:
                 off();
                 colorLight();
                 break;
                case 5:
                 off();
                 rondo();
                 break;
                case 6:
                 off();
                 randomColor();
                 break;
                default:
                break;
              }
            }
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
