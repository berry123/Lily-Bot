/*
  Lily∞Bot
  LilyBot-LEDS.ino
  This program will test that the LEDs are working on the controller

  Carlotta A. Berry, PhD
  September 4, 2022

  Hardware Connections:
  Vmotor - voltage for the motors, not logic level (4.5-13.5V)
  Vcc - voltage for the logic levels (Arduinos, 5V)
  GND - shared logic and motor ground

  Yellow LED pin 7
  Red LED pin 6
  Green LED pin 5
  Blue LED pin 4
*/

//state LEDs
int ledPins[4] = {4, 5, 6, 7};
int ylwLED = 4;
int redLED = 5;
int grnLED = 6;
int bluLED = 7;


/********************************************************************************/
void setup()
{
  int waittime = 1000;               //robot wait time
  int baudrate = 9600;              //serial communication baud rate
  for (int i = 0; i < 4 ; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < 4 ; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(waittime);
  }
  for (int i = 3; i > -1; i--) {
    digitalWrite(ledPins[i], LOW);
    delay(waittime);
  }

  Serial.begin(baudrate);           //start serial commnication
  Serial.print("Lily∞bot begin");  //print start message

}

/********************--**********************************************************/
void loop()
{

}


//turn all the LEDS off
void allLedsOff () {
  for (int i = 0; i < 3 ; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
