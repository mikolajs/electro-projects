int laserPin = 10;
int a = 0;

void setup ()
{
   pinMode (laserPin, OUTPUT); 
    Serial.begin(9600);
}
void loop () {
   digitalWrite (laserPin, HIGH); 
   delay(10);
     a = analogRead(A5);
  Serial.println(a);
   delay (500); 
   digitalWrite (laserPin, LOW); 
    delay(10);
     a = analogRead(A5);
  Serial.println(a);
   delay (500); 
   
}
