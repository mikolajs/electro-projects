int led = 3;
int buzzer = 2;
bool on = false;


void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 1000; i+=10){
     tone(buzzer, 50+i);
     if(on){
       on = false;
       digitalWrite(led, HIGH);
     } else {
       on = true;
       digitalWrite(led, LOW);
     }
     delay(1000);
  }
  delay(100);
}
