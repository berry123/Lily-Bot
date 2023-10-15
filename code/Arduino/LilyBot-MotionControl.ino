/*
  Lily∞Bot
  LilyBot-MotionControl.ino
  Control 2 DC motors with TB6612 motor controller (https://www.adafruit.com/product/2448)
  This program will create low level motion control: forward, reverse, spin, turn, pivot, stop

  Carlotta A. Berry, PhD
  August 5, 2022

  Hardware Connections:
  Vmotor - voltage for the motors, not logic level (4.5-13.5V)
  Vcc - voltage for the logic levels (Arduinos, 5V)
  GND - shared logic and motor ground

  INA1, INA2 - two inputs to the Motor A H-bridges
  PWMA - PWM input for the Motor A H-bridges, if you dont need PWM control, connect this to logic high.
  INB1, INB2 - two inputs to the Motor B H-bridges
  PWMB - PWM input for the Motor B H-bridges, if you dont need PWM control, connect this to logic high.
  STBY - standby pin for quickly disabling both motors, pulled up to Vcc thru a 10K resistor. Connect to ground to disable.

  These are 'Vmotor level' power outputs
  Motor A - these are the two outputs for motor A, controlled by INA1, INA2 and PWMA
  Motor B - these are the two outputs for motor B, controlled by INB1, INB2 and PWMB

  Vmotor to VIN
  Vcc to 5V
  GND to ground
  AIN1 to Digital 4
  AIN2 to Digital 5
  BIN1 to Digital 6
  BIN2 to Digital 7
  PWMA and PWMB to Vcc
*/

//state LEDs
int ledPins[3] = {5, 6, 7};
int redLED = 5;
int bluLED = 6;
int grnLED = 7;

//the left motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 8;           //control pin 1 on the motor driver for the left motor
const int AIN2 = 9;            //control pin 2 on the motor driver for the left motor
const int PWMA = 10;            //speed control pin on the motor driver for the left motor

//the right motor will be controlled by the motor B pins on the motor driver
const int PWMB = 11;           //speed control pin on the motor driver for the right motor
const int BIN2 = 12;           //control pin 2 on the motor driver for the right motor
const int BIN1 = 13;           //control pin 1 on the motor driver for the right motor

//robot behaviour variables
int moveTime = 2000;            //amount of time robot will move
int robotSpeed = 100;           //robot speed

/********************************************************************************/
void setup()
{
  for (int i = 0; i < 3 ; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  //for (int i = 0; i < 3 ; i++) {
  //  digitalWrite(ledPins[i], HIGH);
  //}
  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  int baudrate = 9600;              //serial communication baud rate
  Serial.begin(baudrate);           //start serial commnication
  Serial.print("Lily∞bot begin");  //print start message
  int waittime = 5000;               //robot wait time
  delay(waittime);                  //robot delay before moving
  allLedsOff();
}

/********************************************************************************/
void loop()
{
  fwd(100);
  delay(moveTime);
  stop();
  delay(moveTime);
  
  rev(robotSpeed);
  delay(moveTime);
  stop();
  delay(moveTime);

  spin(robotSpeed, 1);
  delay(moveTime);
  stop();
  delay(moveTime);

  spin(robotSpeed, -1);
  delay(moveTime);
  stop();
  delay(moveTime);
  
  pivot(robotSpeed, 1);
  delay(moveTime);
  stop();
  delay(moveTime);

  pivot(robotSpeed, -1);
  delay(moveTime);
  stop();
  delay(moveTime);
  
  turn(robotSpeed, 1);
  delay(moveTime);
  stop();
  delay(moveTime);
  
  turn(robotSpeed, -1);
  delay(moveTime);
  stop();
  delay(moveTime);
}

//robot stop function
void stop() {
  allLedsOff();
  //left motor stop
  digitalWrite(AIN1, LOW);                          //set pin 1 to low
  digitalWrite(AIN2, LOW);                          //set pin 2 to low
  //right motor stop
  digitalWrite(BIN1, LOW);                          //set pin 1 to low
  digitalWrite(BIN2, LOW);                          //set pin 2 to low
}

//robot forward function
void fwd(int speed) {
  digitalWrite(redLED, HIGH);
  digitalWrite(AIN1, HIGH);                         //set pin 1 to high
  digitalWrite(AIN2, LOW);                          //set pin 2 to low
  digitalWrite(BIN1, HIGH);                         //set pin 1 to low
  digitalWrite(BIN2, LOW);                        //set pin 2 to high
  analogWrite(PWMA, abs(speed));    //set forward speed
  analogWrite(PWMB, abs(speed));    //set forward speed
}

//robot reverse function
void rev(int speed) {
  digitalWrite(bluLED, HIGH);
  digitalWrite(AIN1, LOW);                         //set pin 1 to low
  digitalWrite(AIN2, HIGH);                        //set pin 2 to high
  digitalWrite(BIN1, LOW);                         //set pin 1 to low
  digitalWrite(BIN2, HIGH);                        //set pin 2 to high
  analogWrite(PWMA, abs(speed));    //set reverse speed
  analogWrite(PWMB, abs(speed));    //set reverse speed
}

//robot spin function
void spin(int speed, int dir) {
  digitalWrite(grnLED, HIGH);
  if (dir > 0) {
    digitalWrite(AIN1, LOW);                         //set pin 1 to low
    digitalWrite(AIN2, HIGH);                        //set pin 2 to high
    digitalWrite(BIN1, HIGH);                         //set pin 1 to low
    digitalWrite(BIN2, LOW);                        //set pin 2 to high
  } else {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to low
    digitalWrite(AIN2, LOW);                        //set pin 2 to high
    digitalWrite(BIN1, LOW);                         //set pin 1 to low
    digitalWrite(BIN2, HIGH);                        //set pin 2 to high
  }
  analogWrite(PWMA, abs(speed));    //set reverse speed
  analogWrite(PWMB, abs(speed));    //set reverse speed
}

//robot turn function
void turn(int speed, int dir) {
  digitalWrite(redLED, HIGH);
  digitalWrite(bluLED, HIGH);
  digitalWrite(AIN1, HIGH);                         //set pin 1 to low
  digitalWrite(AIN2, LOW);                        //set pin 2 to high
  digitalWrite(BIN1, HIGH);                         //set pin 1 to low
  digitalWrite(BIN2, LOW);                        //set pin 2 to high
  if (dir > 0) {
    analogWrite(PWMA, robotSpeed*1.5);
    analogWrite(PWMB, robotSpeed*0.5);
  }
  else {
    analogWrite(PWMA, robotSpeed*0.5);
    analogWrite(PWMB, robotSpeed*1.5);
  }
}

//robot pivot function
void pivot(int speed, int dir) {
  digitalWrite(bluLED, HIGH);
  digitalWrite(grnLED, HIGH);
  digitalWrite(AIN1, HIGH);                         //set pin 1 to low
  digitalWrite(AIN2, LOW);                        //set pin 2 to high
  digitalWrite(BIN1, HIGH);                         //set pin 1 to low
  digitalWrite(BIN2, LOW);                        //set pin 2 to high
  if (dir > 0) {
    analogWrite(PWMA, 0);
    analogWrite(PWMB, abs(speed));
  }
  else {
    analogWrite(PWMA, abs(speed));
    analogWrite(PWMB, 0);
  }
}

//turn all the LEDS off
void allLedsOff () {
  for (int i = 0; i < 3 ; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}