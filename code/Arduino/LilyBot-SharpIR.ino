/*
  Lily∞Bot
  LilyBot-Sharp IR.ino
  This program will test that the LEDs are working on the controller

  Carlotta A. Berry, PhD
  September 4, 2022
  These type of distance sensors tend to be a bit noisy, so it is recommended to add a capacitor between Vcc and GND.
  The datasheet suggests a capacitor of 10 µF or more (I used 220 µF). Connect the positive lead of the capacitor to
  the Vcc wire connection and the negative lead to the GND wire connection (see picture). Capacitors are often marked
  with a stripe which indicates the negative lead. The positive lead is often longer then the negative lead.
  Reference: https://www.makerguides.com/sharp-gp2y0a21yk0f-ir-distance-sensor-arduino-tutorial/

  Hardware Connections:
  Vmotor - voltage for the motors, not logic level (4.5-13.5V)
  Vcc - voltage for the logic levels (Arduinos, 5V)
  GND - shared logic and motor ground

  Distance (cm) = 29.988 X POW(Volt , -1.173)

  Sharp GP2Y0A21YK0F IR Connections (10 - 80 cm range) = 4 inches to 32 inches
  front A0
  back A1
  left A2
  right A3

  Yellow LED pin 7
  Red LED pin 6
  Green LED pin 5
  Blue LED pin 4
*/

//state LEDs
int ledPins[4] = {10, 11, 12, 13};
int ylwLED = 10;
int redLED = 11;
int grnLED = 12;
int bluLED = 13;


/********************************************************************************/
void setup()
{
  int waittime = 1000;               //robot wait time
  int baudrate = 9600;              //serial communication baud rate
  for (int i = 0; i < 4 ; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  allLEDSon();
  delay(100);
  allLEDSoff();
  delay(100);
  Serial.begin(baudrate);           //start serial commnication
  Serial.print("Lily∞bot begin");  //print start message

}

/********************--**********************************************************/
void loop()
{
  if ((readIR()) < 6) {
    digitalWrite(ylwLED, HIGH);
    Serial.println("yellow");
  } else if (readIR() < 8) {
    digitalWrite(redLED, HIGH);
    Serial.println("red");
  } else if (readIR() < 10) {
    digitalWrite(bluLED, HIGH);
    Serial.println("blue");
  } else {
    digitalWrite(grnLED, HIGH);
    Serial.println("green");
  }
  delay(100);
  allLEDSoff();
  delay(100);
}


//turn all the LEDS off
void allLEDSoff () {
  for (int i = 0; i < 4 ; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// turn ON all LEDs
void allLEDSon() {
  for (int i = 0; i < 4 ; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

float readIR() {
  float val = analogRead(A0);
  float volts = 5 * val / 1024;

  //  Serial.print("volts: ");
  //  Serial.println(volts);

  float dist_cm = 29.988 * pow(volts, -1.173);
  float dist_in = dist_cm / 2.54;
  //  Serial.print("cm: ");
  //  Serial.print(dist_cm);
  //  Serial.print("\tin: ");
  //  Serial.println(dist_in);
  return dist_in;
}
