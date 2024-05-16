
int laser = 7;
int foto = 6;
int in = false;
int n = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(laser, OUTPUT);
  pinMode(foto, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  in = digitalRead(foto);
  if(in  == HIGH) {
      Serial.println("swieci");
      digitalWrite(2, HIGH);
  }
  else {
     digitalWrite(2, LOW);
     Serial.println("nieswieci");
  } 
  if(n & 2) digitalWrite(laser, HIGH);
  else digitalWrite(laser, LOW);
  n++;
  
 //Serial.println(n);
  delay(1000);
}
