/*
  Daisy∞Bot
  DaisyBot-MotionControl.ino
  Control 2 DC motors with TB6612 motor controller (https://www.adafruit.com/product/2448)
  This program will create low level motion control: forward, reverse, spin, turn, pivot, stop

  Carlotta A. Berry, PhD
  FEBRUARY 4, 2023

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

    LEDS
    Arduino pin 52 to yellow LED
    Arduino pin 53 to red LED
    Arduino pin 50 to blue LED
    Arduino pin 51 to green LED

    TB6612 Motor Driver
    Arduino pin 7 PWMB
    Arduino pin 6 BIN2
    Arduino pin 5 BIN1
    Arduino pin 4 AIN1
    Arduino pin 3 AIN2
    Arduino pin 2  PWMA
    Arduino GND GND
    Arduino 5V Vcc
    Arduino VIN Vm
    Left Motor Motor A
    Right Motor Motor B
*/

//switch pin
const int switchPin = A3;

//state LEDs
const int ledPins[4] = { 50, 51, 52, 53 };
const int bluLED = 50;
const int grnLED = 51;
const int ylwLED = 52;
const int redLED = 53;

//the left motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 4;  //control pin 1 on the motor driver for the left motor
const int AIN2 = 3;  //control pin 2 on the motor driver for the left motor
const int PWMA = 2;  //speed control pin on the motor driver for the left motor

//the right motor will be controlled by the motor B pins on the motor driver
const int PWMB = 7;  //speed control pin on the motor driver for the right motor
const int BIN2 = 6;  //control pin 2 on the motor driver for the right motor
const int BIN1 = 5;  //control pin 1 on the motor driver for the right motor

//robot behaviour variables
int moveTime = 2000;   //amount of time robot will move
int robotSpeed = 100;  //robot speed

/********************************************************************************/
void setup() {
  int baudrate = 9600;     //serial communication baud rate
  Serial.begin(baudrate);  //start serial commnication
  delay(100);
  pinMode(switchPin, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //STARTING LIGHT SEQUENCE
  for (int i = 0; i < 4; i++) {
    Serial.print(i);
    digitalWrite(ledPins[i], HIGH);
    delay(1000);
  }
  Serial.println();
  for (int i = 4; i > -1; i--) {
    Serial.print(i);
    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }
  Serial.print("Daisy∞bot begin");  //print start message
}

/********************************************************************************/
void loop() {
  int on = digitalRead(switchPin);
  if (on == 1) {
    fwd(100);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    rev(robotSpeed);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    spin(robotSpeed, 1);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    spin(robotSpeed, -1);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    pivot(robotSpeed, 1);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    pivot(robotSpeed, -1);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    turn(robotSpeed, 1);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 1) {
    turn(robotSpeed, -1);
    delay(moveTime);
    stop();
    delay(moveTime);
    on = digitalRead(switchPin);
  }
  if (on == 0) {
    Serial.println("Robot Off");
    stop();
  }
}

//robot stop function
void stop() {
  allLedsOff();
  //left motor stop
  digitalWrite(AIN1, LOW);  //set pin 1 to low
  digitalWrite(AIN2, LOW);  //set pin 2 to low
  //right motor stop
  digitalWrite(BIN1, LOW);  //set pin 1 to low
  digitalWrite(BIN2, LOW);  //set pin 2 to low
}

//robot forward function
void fwd(int speed) {
  allLedsOff();
  digitalWrite(grnLED, HIGH);
  digitalWrite(AIN1, HIGH);       //set pin 1 to high
  digitalWrite(AIN2, LOW);        //set pin 2 to low
  digitalWrite(BIN1, HIGH);       //set pin 1 to low
  digitalWrite(BIN2, LOW);        //set pin 2 to high
  analogWrite(PWMA, abs(speed));  //set forward speed
  analogWrite(PWMB, abs(speed));  //set forward speed
}

//robot reverse function
void rev(int speed) {
  allLedsOff();
  digitalWrite(redLED, HIGH);
  digitalWrite(AIN1, LOW);        //set pin 1 to low
  digitalWrite(AIN2, HIGH);       //set pin 2 to high
  digitalWrite(BIN1, LOW);        //set pin 1 to low
  digitalWrite(BIN2, HIGH);       //set pin 2 to high
  analogWrite(PWMA, abs(speed));  //set reverse speed
  analogWrite(PWMB, abs(speed));  //set reverse speed
}

//robot spin function
void spin(int speed, int dir) {
  allLedsOff();
  if (dir > 0) {
    digitalWrite(bluLED, HIGH);
    digitalWrite(AIN1, LOW);   //set pin 1 to low
    digitalWrite(AIN2, HIGH);  //set pin 2 to high
    digitalWrite(BIN1, HIGH);  //set pin 1 to low
    digitalWrite(BIN2, LOW);   //set pin 2 to high
  } else {
    digitalWrite(ylwLED, HIGH);
    digitalWrite(AIN1, HIGH);  //set pin 1 to low
    digitalWrite(AIN2, LOW);   //set pin 2 to high
    digitalWrite(BIN1, LOW);   //set pin 1 to low
    digitalWrite(BIN2, HIGH);  //set pin 2 to high
  }
  analogWrite(PWMA, abs(speed));  //set reverse speed
  analogWrite(PWMB, abs(speed));  //set reverse speed
}

//robot turn function
void turn(int speed, int dir) {
  allLedsOff();
  digitalWrite(AIN1, HIGH);  //set pin 1 to low
  digitalWrite(AIN2, LOW);   //set pin 2 to high
  digitalWrite(BIN1, HIGH);  //set pin 1 to low
  digitalWrite(BIN2, LOW);   //set pin 2 to high
  if (dir > 0) {
    digitalWrite(bluLED, HIGH);
    analogWrite(PWMA, robotSpeed * 1.5);
    analogWrite(PWMB, robotSpeed * 0.5);
  } else {
    digitalWrite(ylwLED, HIGH);
    analogWrite(PWMA, robotSpeed * 0.5);
    analogWrite(PWMB, robotSpeed * 1.5);
  }
}

//robot pivot function
void pivot(int speed, int dir) {
  allLedsOff();
  digitalWrite(AIN1, HIGH);  //set pin 1 to low
  digitalWrite(AIN2, LOW);   //set pin 2 to high
  digitalWrite(BIN1, HIGH);  //set pin 1 to low
  digitalWrite(BIN2, LOW);   //set pin 2 to high
  if (dir > 0) {
    digitalWrite(bluLED, HIGH);
    analogWrite(PWMA, 0);
    analogWrite(PWMB, abs(speed));
  } else {
    digitalWrite(ylwLED, HIGH);
    analogWrite(PWMA, abs(speed));
    analogWrite(PWMB, 0);
  }
}

//turn all the LEDS off
void allLedsOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
