#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include <WiFi.h>
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "camera_pins.h"
const char* ssid = "sweethome12";
const char* password = "9A0033D4";
WiFiServer server(80);
String htmlHeaderOK(size_t);
void addData(WiFiClient&);

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  #if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  #endif

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  /// OV3660? or OV2640
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_XGA);
  
  #if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
  #endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  server.begin();
}

int nr = 1;
unsigned long currentTime = 0;
unsigned long previousTime = 0;
const long timeoutTime = 2000;
String header;

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(client){
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("new client");
    String currentLine = "";    
    while(client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c); 
        header += c;
        if(c == '\n'){
          if(currentLine.length() == 0){
            addData(client);
            client.println();
            Serial.println(header); 
            client.stop();
            nr++;
            break;
          } else currentLine = ""; 
        } else if(c != '\r') currentLine += c;
      }    
    
          
   
    }
    header = "";
    
    
  }
  delay(5);
  //camera_capture();
  //digitalWrite(4, HIGH);
  //delay(2000);
  //digitalWrite(4, LOW);
  //delay(2000);

}

String htmlHeaderOK(size_t len){
  String h = "HTTP/1.1 200 OK\r\n";
  h += "Content-type: image/jpeg\r\n";;
  h += "Content-Length: " + String(len) + "\r\n";
  h += "Content-Disposition: inline; filename=\"shot.jpg\"\r\n";
  h += "Connection: close\r\n";
  return h;
}

void addData(WiFiClient& client){
   
    // client.println("<!DOCTYPE html><html>");
    // client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    // client.println("<link rel=\"icon\" href=\"data:,\">");
    // client.println("<body><h1>ESP32 Web Server</h1><h2>NR: ");
    // client.println(String(nr));
    // client.println("</h2></body></html>");
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera Capture Failed");
        return;
    }
   client.println(htmlHeaderOK(fb->len));
    //replace this with your own function
    //process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
    Serial.print(fb->width);
    Serial.print("x");
    Serial.print(fb->height);
    Serial.print(" len: ");
    Serial.println(fb->len); 
    //return the frame buffer back to the driver for reuse
    client.write(fb->buf, fb->len+2);
    esp_camera_fb_return(fb);
    client.println();
}
