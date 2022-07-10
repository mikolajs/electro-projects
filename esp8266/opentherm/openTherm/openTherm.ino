#include <OpenTherm.h>


const int inPin = 4;
const int outPin = 5;

OpenTherm ot(inPin, outPin);

void handleInterrupt() {
  ot.handleInterrupt();
}

void setup(){
   Serial.begin(115200);
    Serial.println("Start");
    ot.begin(handleInterrupt);
}

void loop()
{  
   bool enableCentralHeating = true;
   bool enableHotWater = true;
   bool enableCooling = true;
    //Set/Get Boiler Statushjhjh
    ot.setBoilerStatus(enableCentralHeating, enableHotWater, enableCooling);
    //Set Boiler Temperature to 64 degrees C
    ot.setBoilerTemperature(36);
    //Get Boiler Temperature
    float temperature = ot.getBoilerTemperature();
    Serial.println(temperature);
    delay(2000);
}
