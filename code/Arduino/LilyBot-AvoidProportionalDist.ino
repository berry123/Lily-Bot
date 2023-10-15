/*
  //Lily∞Bot
  LilyBot-AvoidDistProportional.ino
  Control 2 DC motors with TB6612 motor controller (https://www.adafruit.com/product/2448)
  This program will create low level motion control: forward, reverse, spin, turn, pivot, stop
  It will then implement proportional feedback obstacle avoidance using 4 HC-SR04 ultrasonic distance sensors

  Carlotta A. Berry, PhD
  August 8, 2022

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
  AIN1 to Digital 8
  AIN2 to Digital 9
  BIN1 to Digital 13
  BIN2 to Digital 12
  PWMA to Digital 10
  PWMB to Digital 11
*/

//state LEDs
int ledPins[4] = {7, 6, 5, 4};
int redLED = 5;     //left LED
int bluLED = 6;     //right LED
int grnLED = 7;     //front LED
int ylwLED = 4;     //back LED

//sonar variables
int trigPins[4] = {2, A2, A0, A4};    //{front,back, left, right}
int echoPins[4] = {3, A3, A1, A5};    //{front,back, left, right}
float dist[4];                          //distance for each sonar 
int maxDetect = 5;                          //maximum detect distance to indicate an obstacle                 

//the left motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 8;           //control pin 1 on the motor driver for the left motor, 
const int AIN2 = 9;            //control pin 2 on the motor driver for the left motor
const int PWMA = 10;            //speed control pin on the motor driver for the left motor

//the right motor will be controlled by the motor B pins on the motor driver
const int PWMB = 11;           //speed control pin on the motor driver for the right motor
const int BIN2 = 12;           //control pin 2 on the motor driver for the right motor
const int BIN1 = 13;           //control pin 1 on the motor driver for the right motor

//robot behaviour variables
int moveTime = 200;            //amount of time robot will move
int robotSpeed = 255;           //robot speed
int propSpeed = 0;                  //robot speed proportional to detect distance
int oneSecond = 1000;           //1s delay time variable
int twoSeconds = 2000;          //2s delay time variable
int waittime = 100;           //robot wait time
int state  = 0;                       //robot state variable {front, back, left, right}


/********************************************************************************/


void setup()
{

  for (int i = 0; i < 4 ; i++) {// this declares the LED pins as outputs
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < 4 ; i++) {//this pin will send ultrasonic pulses out from the distance sensor
    pinMode(trigPins[i], OUTPUT);
  }
  for (int i = 0; i < 4 ; i++) {//this pin will sense when the pulses reflect back to the distance sensor
    pinMode(echoPins[i], INPUT);
  }
  for (int i = 0; i < 4 ; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(waittime);
  }
  // set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  int baudrate = 9600;              //serial communication baud rate
  Serial.begin(baudrate);           //start serial commnication
  Serial.print("Lily∞bot begin");  //print start message

  delay(waittime);                  //robot delay before moving
  for (int i = 3; i > -1 ; i--) {
    digitalWrite(ledPins[i], LOW);
    delay(waittime);
  }
}

/********************************************************************************/
void loop()
{
  for (int i = 0; i < 4 ; i++) {//this pin will send ultrasonic pulses out from the distance sensor
    dist[i] = getDistance(&trigPins[i], &echoPins[i]);
    delayMicroseconds(10);
    //Serial.print(dist[i]);
    //Serial.print("\t");
    if (dist[i] < maxDetect && dist[i] > 0) {
      bitSet(state, i);
      digitalWrite(ledPins[i], HIGH);
      propSpeed = robotSpeed*(1-dist[i]/maxDetect);
      Serial.print("robot speed: ");
      Serial.println(propSpeed);
    } else {
      bitClear(state, i);
      digitalWrite(ledPins[i], LOW);
    }
  }
  //Serial.print("\n");
  //Serial.print(" state (fblr) = ");
  //Serial.println(state,BIN);

  switch (state) {
    case 1: //front obstacle
      Serial.println("front obstacles");
      rev(propSpeed);
      break;
    case 2: //back obstacle
      Serial.println("back obstacle");
      fwd(propSpeed);
      break;
    case 4: //left obstacle
      Serial.println("left obstacle");
      spin(propSpeed, 1); //spin right
      break;
    case 8: //right obstacle
      Serial.println("right obstacle");
      spin(propSpeed, -1); //spin left
      break;      
    default: //no obstacle
      Serial.println("no obstacles");
      stop();
      break;
  }
  
  delay(100);//For testing purposes
}
