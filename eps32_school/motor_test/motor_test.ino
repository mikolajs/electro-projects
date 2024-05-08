
void setup() {
  // put your setup code here, to run once:

    pinMode(0, OUTPUT);
}

void loop() {
 digitalWrite(3, HIGH); 
 digitalWrite(2, LOW);
  delay(2000);
  digitalWrite(3, LOW); 
   digitalWrite(2, HIGH); 
  delay(2000); 

}
