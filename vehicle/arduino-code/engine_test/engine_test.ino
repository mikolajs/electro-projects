

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println("start");
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 delay(5000);
 Serial.println("Stop"); 
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 delay(5000);
}
