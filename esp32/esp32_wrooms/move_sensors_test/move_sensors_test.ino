int i = 0;
#define Radar_pin 16 
#define LED_pin 0 
volatile byte state = LOW;
void setup() {
  Serial.begin(115200);
  pinMode(Radar_pin,INPUT_PULLUP);  
  pinMode(LED_pin, OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(Radar_pin), radar_change, CHANGE);
}

void loop() { 
 digitalWrite(LED_pin, state); 

} 


void radar_change(){
  state= digitalRead(Radar_pin); 
  if (state==1) Serial.println("Motion Detected"); 
  else Serial.println("There is No Motion"); 
} 
