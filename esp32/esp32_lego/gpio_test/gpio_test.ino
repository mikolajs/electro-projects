int gpio1 = 27;
int gpio2 = 26;
int gpio3 = 25;
int gpio4 = 33;
int gpio5 = 32;
int gpio6 = 35;
int gpio7 = 34;

void setup() {
    pinMode(gpio1, OUTPUT);
    pinMode(gpio2, OUTPUT);
    pinMode(gpio3, OUTPUT);
    pinMode(gpio4, OUTPUT);
    pinMode(gpio5, OUTPUT);
    pinMode(gpio6, OUTPUT);
    pinMode(gpio7, OUTPUT);

}

void loop() {
  
  digitalWrite(gpio1, HIGH);
  digitalWrite(gpio2, HIGH);
  digitalWrite(gpio3, HIGH);
  digitalWrite(gpio4, HIGH);
  digitalWrite(gpio5, HIGH);
  digitalWrite(gpio6, HIGH);
  digitalWrite(gpio7, HIGH);

  delay(200);

  digitalWrite(gpio1, LOW);
  digitalWrite(gpio2, LOW);
  digitalWrite(gpio3, LOW);
  digitalWrite(gpio4, LOW);
  digitalWrite(gpio5, LOW);
  digitalWrite(gpio6, LOW);
  digitalWrite(gpio7, LOW);
 
  delay(200);
}
