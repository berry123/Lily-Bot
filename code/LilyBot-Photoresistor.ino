/*
  Lily∞Bot
  LilyBot-Photoresistor.ino
  Carlotta A. Berry, PhD
  FEBRUARY 12, 2023

  This program will photoresistor and 10 kohm resistor
  to track light on the Lily∞Bot 


*/

//state LEDs
const int ledPins[4] = { 4, 5, 6, 7 };
const int ylwLED = 4;
const int redLED = 5;
const int bluLED = 6;
const int grnLED = 7;

const int switchPin = 2;       //robot on-off switch
const int photoresistor = A0;  //photoresistor pin

//the right motor will be controlled by the motor B pins on the motor driver

const int BIN1 = 8;  //control pin 1 on the motor driver for the right motor
const int BIN2 = 9;  //control pin 2 on the motor driver for the right motor
const int PWMB = 10;  //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor A pins on the motor driver
const int PWMA = 11;  //speed control pin on the motor driver for the left motor
const int AIN2 = 12;   //control pin 2 on the motor driver for the left motor
const int AIN1 = 13;   //control pin 1 on the motor driver for the left motor




//robot behaviour variables
int moveTime = 2000;   //amount of time robot will move
int robotSpeed = 100;  //robot speed

//light tracking variables
int ambient;         //ambient room lighting for calibration at start up
int maxLight = 900;  //max light from flashlight


/********************************************************************************/
void setup() {
  int baudrate = 9600;     //serial communication baud rate
  Serial.begin(baudrate);  //start serial commnication
  delay(100);
  //set switch as an input
  pinMode(switchPin, INPUT_PULLUP);
  //set LEDS as an output
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  //set photoresistor as an input
  pinMode(photoresistor, INPUT);

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //STARTING LIGHT SEQUENCE
  for (int i = 0; i < 4; i++) {
    //Serial.print(i);
    digitalWrite(ledPins[i], HIGH);
    delay(100);
  }
  Serial.println();
  for (int i = 4; i > -1; i--) {
    //Serial.print(i);
    digitalWrite(ledPins[i], LOW);
    delay(100);
  }
  ambient = analogRead(photoresistor);
  Serial.print("Daisy∞bot begin");  //print start message
}

/********************************************************************************/
void loop() {
  int on = digitalRead(switchPin);
  int light = analogRead(photoresistor);
  Serial.println(on);

  if (on == 1) {
    light = analogRead(photoresistor);
    Serial.println(light);
    robotSpeed = map(light, maxLight, ambient, 0, 255);  //map robot light to robot motor speed
    robotSpeed = constrain(robotSpeed, 0, 255);          //constrain robot speeds between 0 and 255
    fwd(robotSpeed);                                     //robot will move forward looking for more light
    on = digitalRead(switchPin);
  }

  if (on == 0) {
    Serial.println("Robot Off");
    stop();
    on = digitalRead(switchPin);
  }
}

/********************************* MOTION FUNCTIONS ******************************/
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
