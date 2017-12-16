int _ABVAR_1_Integer = 0 ;
void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}


void setup()
{
  _ABVAR_1_Integer = 36 ;

  __ardublockDigitalWrite(1, HIGH);

}

void loop()
{
}


