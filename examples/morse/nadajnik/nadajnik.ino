
int led = 7;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void kropka(){
   digitalWrite(led, HIGH);
   delay(100);
   digitalWrite(led, LOW);
   delay(100);
}

void kreska(){
   digitalWrite(led, HIGH);
   delay(300);
   digitalWrite(led, LOW);
   delay(100);
}

void przerwa(){
  digitalWrite(led, LOW);
  delay(300);
}

void nadawanie(String tekst) {
  for(int i = 0; i < tekst.length(); i++) {
   if(tekst.charAt(i) == '-') kreska();
   else if(tekst.charAt(i) == '.') kropka();
   else przerwa();
  }
}

String morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
String space = ".-..- ";

String textToMorse(String text) {
  text.toLowerCase();
  String morse = "";
  for(int i =0; i < text.length();i++){
    if(text.charAt(i) >= 'a' && text.charAt(i) <= 'z' ){
      morse += morseCode[(int) text.charAt(i) - 97];
      morse += ' ';
    } else if(text.charAt(i) == ' ') 
      morse += space;
  }
  return morse;
}

void loop() {
  String napis = "SOS";
  nadawanie(textToMorse(napis));
//  delay(2000);
}
