/*na ESP32 C3 superMini nie działa na pinach 5-21, nie wiem czemu.
* temperatura wygląda na zawyżoną o jakieś 2°C? albo po służszym czasie dopiero się obniża?
*/

#include <DHT.h>

DHT dht(2, DHT22);

bool measureAndSendData(){

  double  h = dht.readHumidity();
  double  t = dht.readTemperature();
  Serial.println("t = " + String(t, 2) + " h = " + String(h, 2));
  if(t == NAN || h == NAN) return false;
  else return true;
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(100);
}

void loop() {
  measureAndSendData();
  delay(1000);

}
