/*
//1) Alla pressione di un bottone di accende un LED
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
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//2) Se un oggetto é più vicino di 5 CM si accende un LED

/*
#include "Ultrasonic.h"
Ultrasonic ultrasonic(0);

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); //Led integrato
  //  myservo.attach(4);  // attaches the servo on pin 4 to the servo object
}
void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);                     //0~400cm
  if (RangeInCentimeters < 5)
  {
    analogWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    analogWrite(LED_BUILTIN, LOW);
  }
  delay(25);
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//2.1 il led (Adressable) cambia a seconda della distanza


#include "Ultrasonic.h"
int led = 5;
Ultrasonic ultrasonic(0);
int val;    // variable to read the value from the analog pin

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm
  val = map(RangeInCentimeters, 0, 300, 0, 255);     // scale it to use it with the servo (value between 0 and 180)
  if(RangeInCentimeters < 5){
    analogWrite(led, 0);
  }else{
    analogWrite(led, val);
  } // myservo.write(val);
  delay(25);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//3) Il LED adressable é sempre rosso. Se la temperatura scende sotto una certa soglia diventa blu
