#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial); // Czekaj na otwarcie monitora portu szeregowego
  delay(2000);
  Serial.println("\nSkaner I2C dla ESP32-C3 SuperMini");
  Wire.begin(0, 1); // SDA = GPIO 0, SCL = GPIO 1
}

void loop() {
  byte error, address;
  int nDevices = 0;
  Serial.println("Skanowanie...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Znaleziono urzadzenie pod adresem: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }
  if (nDevices == 0) Serial.println("Nie znaleziono ZADNYCH urzadzen I2C\n");
  else Serial.println("Skanowanie zakonczone.\n");
  delay(5000);
}