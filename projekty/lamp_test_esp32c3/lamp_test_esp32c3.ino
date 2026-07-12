#define LED_FLASH_PIN 8
#define LIGTH_SENSOR 0
#include <SoftwareSerial.h>
#include "LD2420.h"

// Define RX and TX pins for SoftwareSerial
#define RX_PIN 21
#define TX_PIN 20
SoftwareSerial sensorSerial(RX_PIN, TX_PIN);
LD2420 radar;  // Use default constructor

// Track last distance to detect changes
int lastDistance = -1;
bool wasDetecting = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  pinMode(LED_FLASH_PIN, OUTPUT);
  pinMode(LIGTH_SENSOR, INPUT);
  Serial.println("=== Simple Motion Detection ===");
  
  // Initialize SoftwareSerial for LD2420
  sensorSerial.begin(115200);
  // Initialize the radar sensor
  if (radar.begin(sensorSerial)) {
    Serial.println("Radar ready. Waiting for motion...");
  } else {
    Serial.println("Failed to initialize radar!");
    while (1) delay(1000);
  }
  
  // Configure sensor
  radar.setDistanceRange(0, 600);
  radar.setUpdateInterval(50); // 20Hz update rate
}

void loop() {
  int lightVal = analogRead(LIGTH_SENSOR);
  Serial.println(lightVal);
  if(lightVal > 200)
    digitalWrite(LED_FLASH_PIN, HIGH); 
  else 
    digitalWrite(LED_FLASH_PIN, LOW); 

 radar.update();  // Update radar readings
  
  // Check if motion is detected
  bool isDetecting = radar.isDetecting();
  int currentDistance = radar.getDistance();
  
  if (isDetecting) {
    // Only print when distance changes
    if (currentDistance != lastDistance) {
      Serial.print("Motion detected at ");
      Serial.print(currentDistance);
      Serial.println("cm");
      
      lastDistance = currentDistance;
      wasDetecting = true;
    }
  } else {
    // Motion stopped - reset for next detection
    Serial.println("Not detected");
    if (wasDetecting) {
      lastDistance = -1;
      wasDetecting = false;
    }
  }

  delay(100);
}