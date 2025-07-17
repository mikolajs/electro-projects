//PIR MINI left Power 5V or 3.3V, right GND, center digital pin

int SENSOR_PIN = 16;
int LED = 5;
int newState;
int oldState;

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED, OUTPUT);
  Serial.printf("Wait 10 secs for the PIR sensor to calibrate properly\r\n");
  delay(1000 * 10);
  oldState = digitalRead(SENSOR_PIN); // read the starting state
  digitalWrite(LED, LOW);
  pinMode(BUILTIN_LED, OUTPUT);  
}

void loop() {
  newState = digitalRead(SENSOR_PIN); // read current state

  if(oldState != newState) {
    if (newState == HIGH) {
      Serial.println("Movement detected!");
      digitalWrite(LED, HIGH);
    } else {
      Serial.println("Movement not detected!");
      digitalWrite(LED, LOW);
    }
    oldState = newState;
  }  
   
   delay(100);
   //digitalWrite(BUILTIN_LED, LOW);
}