 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define BMP_SCK 14
#define BMP_MISO 12
#define BMP_MOSI 13
#define BMP_CS 15
 
Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);
 
void setup() {
Serial.begin(115200);
Serial.println(F("BMP280 test"));
int n = 10;
if (!bme.begin()) { 
Serial.println("Could not find a valid BMP280 sensor, check wiring!");
while (n--) Serial.println(n);
}
}
 
void loop() {
Serial.print("Temperature = ");
Serial.print(bme.readTemperature());
Serial.println(" *C");
 
Serial.print("Pressure = ");
Serial.print(bme.readPressure());
Serial.println(" Pa");
 
Serial.print("Approx altitude = ");
Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
Serial.println(" m");
 
Serial.println();
delay(2000);
}
