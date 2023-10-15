/*
  Daisy∞Bot
  DaisyBot-IR_Sonar.ino

  This program will read the sonar on the left side of Daisy and the IR on the right side of Daisy and use them to move the robot

  Carlotta A. Berry, PhD
  FEBRUARY 18, 2023

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

    Sonar Trigger A14
    Sonar Echo A15
    Infrared A13

    green LED 51
    blue LED 50
    yellow LED 52
    red LED 53
*/

//switch pin
const int switchPin = A3;

//state LEDs
const int ledPins[4] = { 50, 51, 52, 53 };
const int bluLED = 50;
const int grnLED = 51;
const int ylwLED = 52;
const int redLED = 53;

// range sensors
const int irPin = A13;
const int trigPin = A14;
const int echoPin = A15;
int snrDist;
int irDist;
int detectDist = 10;


//the left motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 4;  //control pin 1 on the motor driver for the left motor
const int AIN2 = 3;  //control pin 2 on the motor driver for the left motor
const int PWMA = 2;  //speed control pin on the motor driver for the left motor

//the right motor will be controlled by the motor B pins on the motor driver
const int PWMB = 7;  //speed control pin on the motor driver for the right motor
const int BIN2 = 6;  //control pin 2 on the motor driver for the right motor
const int BIN1 = 5;  //control pin 1 on the motor driver for the right motor

//robot behaviour variables
int moveTime = 100;    //amount of time robot will move
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

  // set range sensors as inputs and outputs
  pinMode(irPin, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  //STARTING LIGHT SEQUENCE
  for (int i = 0; i < 4; i++) {
    Serial.print(i);
    digitalWrite(ledPins[i], HIGH);
    delay(200);
  }
  Serial.println();
  for (int i = 4; i > -1; i--) {
    Serial.print(i);
    digitalWrite(ledPins[i], LOW);
    delay(200);
  }
  Serial.print("Daisy∞bot begin");  //print start message
}

/********************************************************************************/
void loop() {
  int on = digitalRead(switchPin);
  int snrDist = readSonar();
  Serial.print("sonar: ");
  Serial.print(snrDist);
  int irDist = readIR();
  Serial.print("\tIR: ");
  Serial.println(irDist);
  if (on == 1) {
    if (snrDist < detectDist && irDist < detectDist) {
      fwd(robotSpeed);
      //delay(moveTime);
      //stop();
    } else if (snrDist < detectDist) {
      pivot(robotSpeed, 1);
      //delay(moveTime);
      //stop();
    } else if (irDist < detectDist) {
      pivot(robotSpeed, 0);
      //delay(moveTime);
      //stop();
    } else {
      stop();
    }
  }
  on = digitalRead(switchPin);

  if (on == 0) {
    //Serial.println("Robot Off");
    stop();
    on = digitalRead(switchPin);
  }
  delay(100);
}


// Sonar get distance
//get sonar distance
float readSonar() {
  float echoTime;            //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;  //variable to store the distance calculated from the echo time

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance;              //send back the distance that was calculated
}

//Infrared get Distance
float readIR() {
  float val = analogRead(irPin);
  float volts = 5 * val / 1024;
  float dist_cm = 29.988 * pow(volts, -1.173);
  float dist_in = dist_cm / 2.54;

  return dist_in;
}



//// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Motion Functions @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//robot stop function
void stop() {
  allLedsOff();
  digitalWrite(redLED, HIGH);
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
  digitalWrite(AIN1, LOW);       //set pin 1 to high
  digitalWrite(AIN2, HIGH);        //set pin 2 to low
  digitalWrite(BIN1, LOW);       //set pin 1 to low
  digitalWrite(BIN2, HIGH);        //set pin 2 to high
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
  digitalWrite(AIN1, LOW);   //set pin 1 to low
  digitalWrite(AIN2, HIGH);  //set pin 2 to high
  digitalWrite(BIN1, LOW);   //set pin 1 to low
  digitalWrite(BIN2, HIGH);  //set pin 2 to high
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
