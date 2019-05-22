int mic = 5;

void setup() {
   Serial.begin(9600);
   //pinMode(mic, INPUT);
}

void loop() {
   int sound = digitalRead(mic); 
   Serial.println(sound);
}
