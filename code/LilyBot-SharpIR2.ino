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
https://hellocircuits.com/2013/04/24/how-to-make-a-sharp-ir-sensor-linear/#:~:text=Here%20is%20an%20equation%20tweaked%20for%20the%20longer,%3D%2030431%20%2A%20pow%20%28sensorValue%2C%20-1.169%29%20%2F%2F%20centimeters
  
  Hardware Connections:
  Vmotor - voltage for the motors, not logic level (4.5-13.5V)
  Vcc - voltage for the logic levels (Arduinos, 5V)
  GND - shared logic and motor ground

  Sharp GP2YOA1YK IR Connections (10 - 80 cm range)
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
  Serial.println(readIR());
  delay(100);
}


//turn all the LEDS off
void allLedsOff () {
  for (int i = 0; i < 3 ; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

float readIR(){
  float volt=analogRead(A0);
  float dist_cm = 12343.85 * pow(volt, -1.15)
  float dist_in = dist_cm/2.54;
}
