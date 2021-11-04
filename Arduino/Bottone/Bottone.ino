const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //Led integrato
  pinMode(buttonPin, INPUT); //Bottone
}

void loop() {

  buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
