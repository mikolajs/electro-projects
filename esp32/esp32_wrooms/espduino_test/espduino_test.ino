int n = 0;
const int s = 14;
//const int pinsOut[s] = {2, 4, 5, 12, 13, 14, 16, 17, 18, 19, 23, 25, 26, 27};
const int pinsIn[s] = {2, 4, 5, 12, 13, 14, 16, 17, 18, 19, 23, 25, 26, 27};
int in = 0;
void setup() {
  //pinMode(2, OUTPUT); //BUILDIN LED
  //for(int i = 0; i < s; i++) pinMode(pinsOut[i], OUTPUT);
  for(int i = 0; i < s; i++) pinMode(pinsIn[i], INPUT);
  Serial.begin(115200);
}

void loop() {
  //for(int i = 0; i < s; i++) digitalWrite(pinsOut[i], HIGH);
  delay(1000);                     
  //for(int i = 0; i < s; i++) digitalWrite(pinsOut[i], LOW);
  delay(1000);   
  Serial.print("n = ");
  Serial.println(n);  
  n++;              
}
