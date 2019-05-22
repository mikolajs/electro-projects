#include "BLEDevice.h"                                                                                       // As a starting point we get a class "BLEDevive" that consists of some Bluetooth Low Energy (LE) functions.  https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/src/BLEDevice.h 
static BLEAddress *addressOfOurThermometer;                                                                  // To be able to take a connection to a BLE (server) device, one must know the 6 byte long address of that BLE device. Here we will mostly use a pointer (the * marking here) to the memory location where that address is saved.
BLERemoteService* remoteServiceOfTheThermometer;                                                             // Here we create a model of a services that are offered to us by the remote BLE server that we are connected to. 
static BLERemoteCharacteristic* characteristicOfTheTemperatureMeasurementValue;                              // A service (mentioned the previous line) always contains one or more BLE variable (that are called a characteristic). Here we create a model for such characteristics.
BLERemoteDescriptor* descriptorForStartingAndEndingNotificationsFromCharacteristic;                          // A descriptor of a charasteristic (that was mentioned at the previous line) contains information on how to use or modify that characteristic. For instance the existence of the descriptor 0x2902 in the middle of the "readTempAsString" function tells us how to get automatic broadcasts that contain notifications of the value of the temperature-measurement-value-characteristic.
BLEClient*  thisOurMicrocontrollerAsClient;                                                                  // At teh previous lines we modelled the services that a BLE server offers. At this line we create a model of our ESP32 BLE client that is using those services.
String receivedTemperatureValue = ""; unsigned long startTime;                                               // The string variable will contain the latest temperature measurement value that is received from the Xiaomi BLE thermometer. The other one is a timestamp.

class theEventsThatWeAreInterestedInDuringScanning: public BLEAdvertisedDeviceCallbacks {                    // As we later construct a scanner, we will be interested in certain events that occur during the scanning process
  void onResult(BLEAdvertisedDevice advertisedDevice) {                                                      // The onResult event is important for us when we are scanning for Bluetooth servers as this function will be called each time a new device is found.
    if (advertisedDevice.getName() == "MJ_HT_V1") {                                                          // We are scannig to find a device named "MJ_HT_V1". Here we check if we have found it.
      advertisedDevice.getScan()->stop();                                                                    // If our device was found, we don't need to scan any further and we save the address of the desired device
      addressOfOurThermometer = new BLEAddress(advertisedDevice.getAddress()); } } };                        // We save the address of the device that had the name "MJ_HT_V1".

static void notifyAsEachTemperatureValueIsReceived(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* receivedNotification, size_t length, bool isNotify) { // The temperature measurement value broadcasts are notifications that each time that they come fire this function.
  if (receivedTemperatureValue.length() >= 4) return;                                                                                                                // If we already have gotten a valid temperature measurement value (or an error announcement) these is no need to analyze further this newest notificaton
  for (int i=2; i<=5; i++) receivedTemperatureValue += (char)*(receivedNotification+i); }                                                                            // The notification of this particular thermometer happens to be an ASCII coded series of characters that is in a nicely readable format like "T=22.6 H=32.2\00" // for (int i=0; i<length; i++) Serial.print((char)*(receivedNotification+i)); // The notification happens to be an ASCII coded series of characters in nicely readable format like "T=22.6 H=32.2\00"

String readTempAsString(void) {
  if (thisOurMicrocontrollerAsClient->isConnected() == false) {thisOurMicrocontrollerAsClient->disconnect(); delay(20); thisOurMicrocontrollerAsClient->connect(*addressOfOurThermometer); startTime = millis(); } // Here the our ESP32 as a client asks for a connection to the desired target device.
  if( thisOurMicrocontrollerAsClient->isConnected() == false ) {return "e4 Connection couln't be established";}                                                                                                    // Here we check if we succeded to make the connection.
  if (remoteServiceOfTheThermometer == nullptr) { remoteServiceOfTheThermometer = thisOurMicrocontrollerAsClient->getService("226c0000-6476-4566-7562-66734470666d"); }                                            // Here we are obtaining a reference to the service that we are after (hosted by the wireless BLE thermometer).
  if (remoteServiceOfTheThermometer == nullptr) {thisOurMicrocontrollerAsClient->disconnect(); return "e6 ERROR Found the thermometer, but failed to find the needed service. Try again later.";}                  
  if (characteristicOfTheTemperatureMeasurementValue == nullptr) { characteristicOfTheTemperatureMeasurementValue = remoteServiceOfTheThermometer->getCharacteristic("226caa55-6476-4566-7562-66734470666d"); }    // Here we are obtain a reference to a sensor characteristic (of the service that is hosted by the wireless BLE thermometer).
  if (characteristicOfTheTemperatureMeasurementValue == nullptr) {thisOurMicrocontrollerAsClient->disconnect(); return "e8 ERROR Found the thermometer and its service, but failed to find the neede characteristic. Try again later.";} 
  characteristicOfTheTemperatureMeasurementValue->registerForNotify(notifyAsEachTemperatureValueIsReceived); 
  if (descriptorForStartingAndEndingNotificationsFromCharacteristic == nullptr) { descriptorForStartingAndEndingNotificationsFromCharacteristic = characteristicOfTheTemperatureMeasurementValue->getDescriptor(BLEUUID((uint16_t)0x2902));}                                                                                 // Here we are enabling the notifying of the sensor characteristic (i.e. temperature measurement value).
  if (descriptorForStartingAndEndingNotificationsFromCharacteristic == nullptr) {thisOurMicrocontrollerAsClient->disconnect(); return "e10 ERROR Found the thermometer, its service and its charasteristic, but failed to find othe needed descriptor at UUID = 0x2902. Try again later.";} 
  receivedTemperatureValue = "";
  uint8_t startNotifications[2] = {0x01,0x00}; descriptorForStartingAndEndingNotificationsFromCharacteristic->writeValue(startNotifications, 2, false);                                                                                                                                                                      // Ideas: https://stackoverflow.com/questions/1269568/how-to-pass-a-constant-array-literal-to-a-function-that-takes-a-pointer-without
  startTime = millis(); while( ( (millis() - startTime) < 5000) && (receivedTemperatureValue.length() < 4) ) { if (thisOurMicrocontrollerAsClient->isConnected() == false) {return "e12 ERROR After succesfully done all the setup we unexpectidly lost the connection. Try moving the thermometer closer to the ESP32.";} } // https://github.com/nkolban/esp32-snippets/issues/228  https://github.com/nkolban/esp32-snippets/issues/228  https://forum.arduino.cc/index.php?topic=122413.0
  characteristicOfTheTemperatureMeasurementValue->registerForNotify(NULL);                                                                                             // Stop reacting to futher notifications...
  uint8_t endNotifications[2] = {0x00,0x00}; descriptorForStartingAndEndingNotificationsFromCharacteristic->writeValue(endNotifications, 2, false);                    // ...and ask the thermometer to stop sending notifications
  if (receivedTemperatureValue.length() < 4) return "e14 No proper temperature measurement value catched.";
  return receivedTemperatureValue; }

//  ****************************************************************************************
//  *********     PUT YOUR LIBRARIES AND GLOBAL VARIABLES HERE.  FOR INSTANCE :    *********
//  ****************************************************************************************
// Uncomment the next two lines (and declare the GPIO pins for SCL, SDA and RESET) if your ESP32 has an I2C SSD1306 128x64 OLED display:
// #include <U8g2lib.h> // To use this library you must download it by choosing at your Arduino IDE: Sketch -> Include Libraries -> Manage Libraries -> Search for "ESP32 SSD1306" -> choose "ESP8266 and ESP32 Oled Driver for SSD1306 display" -> Instal -> Close
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /*SCL*/ 15, /*SDA*/ 4, /*RESET*/ 16); bool iso=true; // https://yoursunny.com/t/2018/happy-new-year-2018/

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(0);
  BLEDevice::init("OptionalTheNameOfTheBleEnvironmentAtOurEsp32");                                // This first BLEDevice function initializes the ESP32's local Bluetooth LE environment.
  BLEScan* myBLEScanner = BLEDevice::getScan();                                                   // And this BLEDevice function generates a tool "myBLEScanner" that we use later for searching for other Bluetooth LE devices.  https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/src/BLEScan.h
  myBLEScanner->setAdvertisedDeviceCallbacks(new theEventsThatWeAreInterestedInDuringScanning()); // There are some "theEventsThatWeAreInterestedInDuringScanning()" , especially those that inform us each time when we a new Bluetooth LE device is detected. 
  myBLEScanner->setActiveScan(true);                                                              // Active scanning
  while (addressOfOurThermometer == nullptr) {
    myBLEScanner->start(30); startTime=millis();                                                  // Here we start the scan to run for 30 seconds (and blocks the program for those seconds). It returns an object that contains the information about each unique device found.
    while ( (millis()-startTime <50) && (addressOfOurThermometer == nullptr) ) { delay(1); } }    // The start-command should be a blocking call, but in my tests the address got always established only about 10ms after that call (that is << 50ms).
  thisOurMicrocontrollerAsClient = BLEDevice::createClient();                                     // A BLE Client is medelled as the BLEClient class. Here we create an (yet unconnected) instance of that class.
  
  //  *************************************************************************************
  //  *********    PUT YOUR OWN SETUP CODE HERE, TO RUN ONCE.  FOR INSTANCE :     *********
  //  *************************************************************************************
  // Uncomment the next line if your ESP32 is conected to an I2C SSD1306 128x64 OLED display:
  // u8g2.begin(); // https://github.com/olikraus/u8g2/wiki/fntlistall#54-pixel-height
}

void loop() {
  //  ************************************************************************************************
  //  *********      PUT YOUR OWN MAIN CODE HERE, TO BE RUN REPEATEDLY.  FOR INSTANCE :      *********
  //  ************************************************************************************************
  Serial.print("\n\r  =====>  New temperature value: " + readTempAsString() +" deg C");
  // For an OLED display uncomment the next line (if your ESP32 is conected to an I2C SSD1306 128x64 OLED display):
  // if (iso == true) {u8g2.setFont(u8g2_font_logisoso54_tf); iso=false;} else {u8g2.setFont(u8g2_font_osb41_tf); iso=true;} char currentTemperature[5]; readTempAsString().toCharArray(currentTemperature, 5);  u8g2.clearBuffer(); u8g2.drawStr(0, 60, currentTemperature); u8g2.sendBuffer(); // https://robotzero.one/heltec-wifi-kit-32/  // https://github.com/olikraus/u8g2/wiki/u8g2reference#drawstr
}
