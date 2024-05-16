///ESP32 Adafruit QT Py
//przy podłączaniu kabla wcisnąć boot i dopier puścić. (z lewej)
///uruchomienie wymaga klinięcia resetu (z prawej)
int n = 1;
const int s = 13;
const int pinsOut[s] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 21};
// 1, 6, 7, 8,  9, 10, 11, uszkodzone?  34, 35, 36, 39 only input
const int t = 11;
const int pinsIn[t] = {0, 1, 2, 3, 4, 5, 6, 7,  10};
int in = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(laser, OUTPUT);
  //pinMode(foto, INPUT);
  for(int i = 0; i < s; i++) pinMode(pinsOut[i], OUTPUT);
  //for(int i = 0; i < t; i++) pinMode(pinsIn[i], INPUT);
  Serial.begin(115200);
}

void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);  // 
  //digitalWrite(laser, HIGH);
  //in = digitalRead(foto);
  for(int i = 0; i < s; i++) digitalWrite(pinsOut[i], HIGH);
  delay(1000);                      // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);   
  //digitalWrite(laser, LOW);
  for(int i = 0; i < s; i++) digitalWrite(pinsOut[i], LOW);
  //for(int i = 0; i < t; i++) digitalRead(pinsIn[i]);
	
  delay(1000);   
  Serial.print(n);
  Serial.print(" : ");
  n++;
  Serial.println("next");                // wait for a second
}
