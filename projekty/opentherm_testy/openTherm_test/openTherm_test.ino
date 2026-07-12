#include <OpenTherm.h>

// Piecyk: OT1 z prawej - żółty, OT2 z lewej - zielony 
// (w moim D1 mini zielony jest zamieniony z czerwonym w stosunku do kabla wyjściowego)

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
   bool enableHotWater = false;
   bool enableCooling = true;
    //Set/Get Boiler Statushjhjh
    ot.setBoilerStatus(enableCentralHeating, enableHotWater, enableCooling);
    //Set Boiler Temperature to 64 degrees C
    ot.setBoilerTemperature(36.0);
    //Get Boiler Temperature
    float temperature = ot.getBoilerTemperature();
    Serial.println(temperature);
    delay(5000);
}
