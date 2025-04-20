const int pinsTab[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 11; i++){
    pinMode(pinsTab[i], OUTPUT);
  }
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
}

void loop() {
  for(int i = 0; i < 11; i++) digitalWrite(pinsTab[i], HIGH); 
  digitalWrite(20, HIGH); 
  digitalWrite(21, HIGH); 
  delay(1000);
  for(int i = 0; i < 11; i++) digitalWrite(pinsTab[i], LOW); 
  digitalWrite(20, LOW); 
  digitalWrite(21, LOW); 
  delay(1000); 

}
