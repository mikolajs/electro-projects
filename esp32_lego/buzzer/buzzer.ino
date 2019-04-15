int ch = 1;

void setup() {
  ledcSetup(ch,1E5,12);
  ledcAttachPin(25,ch);
}
void loop() {
   ledcWriteTone(ch,440);
   delay(500);
   ledcWriteTone(ch,680);
   delay(500);
}
