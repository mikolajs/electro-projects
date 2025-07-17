#include <U8g2lib.h>
#define OLED_RESET U8X8_PIN_NONE  // Reset pin
#define OLED_SDA 5
#define OLED_SCL 6


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);
int width = 72;
int height = 40;
int xOffset = 30;  // = (132-w)/2
int yOffset = 12;  // = (64-h)/2


int c = 0;

void handle_oled(int c) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(xOffset + 0, yOffset + 10, "Display is working!");
  u8g2.drawStr(xOffset + 0, yOffset + 20, "Have fun with it");
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "Uptime: %ds", c);
  u8g2.drawStr(xOffset + 0, yOffset + 30, buffer);
  u8g2.sendBuffer();
}


void setup(void) {
  u8g2.begin();
  u8g2.setContrast(255);     // set contrast to maximum
  u8g2.setBusClock(400000);  //400kHz I2C
  Serial.begin(115200);
}

void loop(void) {
  handle_oled(c);
  Serial.println("next second");
  c++;
  delay(1000);
}
