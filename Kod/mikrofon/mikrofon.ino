//sprawdzam klaśnięcie nie działa!!!!!!!!!!!!
int mic = 36;

void setup() {
   Serial.begin(115200);
  pinMode(mic, INPUT);
}

void loop() {
   int sound = digitalRead(mic); 
   if(sound == HIGH) Serial.println("klask");
   else Serial.println("Nic");
   delay(100);
}
