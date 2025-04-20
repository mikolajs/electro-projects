int a = 0;
int led = 7;
int b = 200;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

int poziom(){
  delay(10);
  if(analogRead(A5) < 200) return 1;
  else return 0;
}

int czytaj(){
  int n = 0;
  for(int i = 0; i < 10; i++){
    if(analogRead(A5) < 200) n++;
    delay(10);
  }
  return n;
}

char znak(){
   int s = 0;
  while(czytaj() >= 8){
    s += 1;
  } 
  Serial.print(s);
  Serial.print(" ");
    if(s == 1) return '.';
    else if(s == 3) return '-';
    else return '?';
}

void loop() {
  int n = 0;
  //while(analogRead(A5) > 200) { delay(1);}
  while(true) {
    Serial.print(poziom());
    Serial.print(" ");
    if(n++ % 10 == 0) Serial.println();
  }
  
}
