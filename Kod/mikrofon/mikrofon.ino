//Najlepiej użyć analogRead. Wyregulować pokrętłem czułość
// musi być ciągle sprawdzany, żeby trafić na klaśnięcie.!!!!!!
int mic = 33;

void setup() {
  Serial.begin(115200);
  pinMode(mic, INPUT);
}
int n = 0;
void loop() {
   int sound = analogRead(mic); 
   //Serial.println(sound);
   if(sound >  100) {
   
    n += 1;
     Serial.println(String(n) + " klask poziom: " + String(sound));
     delay(1000);
   }
   //else Serial.println("Nic");
   delay(5);
}
