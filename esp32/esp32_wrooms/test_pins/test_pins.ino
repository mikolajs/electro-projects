///ESP-Wrooms-32
int n = 1;
const int laser = 0;
const int foto = 15;
const int s = 21;
const int pinsOut[s] = {0, 16, 15, 2, 4, 17, 5, 18, 19, 21, 22, 23, 3, 12, 13, 14, 25, 26, 27, 32, 33};
// 1, 6, 7, 8,  9, 10, 11, uszkodzone?  34, 35, 36, 39 only input
const int t = 25;
const int pinsIn[t] = {34, 35, 37, 39, 0, 16, 15, 2, 4, 17, 5, 18, 19, 21, 22, 23, 3, 12, 13, 14, 25, 26, 27, 32, 33};
int in = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  //pinMode(laser, OUTPUT);
  //pinMode(foto, INPUT);
  //for(int i = 0; i < s; i++) pinMode(pinsOut[i], OUTPUT);
  for(int i = 0; i < t; i++) pinMode(pinsIn[i], INPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(2, HIGH);  // 
  //digitalWrite(laser, HIGH);
  //in = digitalRead(foto);
  //for(int i = 0; i < s; i++) digitalWrite(pinsOut[i], HIGH);
  delay(1000);                      // wait for a second
  digitalWrite(2, LOW);   
  //digitalWrite(laser, LOW);
  //for(int i = 0; i < s; i++) digitalWrite(pinsOut[i], LOW);
  for(int i = 0; i < t; i++) digitalRead(pinsIn[i]);
	
  delay(1000);   
  Serial.print(n);
  Serial.print(" : ");
  n++;
  Serial.println("next");                // wait for a second
}
