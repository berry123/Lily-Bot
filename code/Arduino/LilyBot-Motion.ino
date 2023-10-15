/*
  Berry-Asst 1 2.22.22
  This code will include all of the movement functions for my robot.
  forward, reverse, stop, spin, turn, pivot
  square, circle, figure 8
*/

/* Hardware Connections */
//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

//sonar distance variables
const int trigPin = 6;
const int echoPin = 5;

int switchPin = 7;             //switch to turn the robot on and off
float distance = 0;            //variable to store the distance measured by the distance sensor

//robot behavior variables
int backupTime = 300;           //amount of time that the robot will back up when it senses an object
int turnTime = 200;             //amount that the robot will turn once it has backed up
int oneSecond = 1000;         //one second variable

/********************************************************************************/
void setup()
{
  //this function only runs once
  pinMode(trigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor
  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);                       //begin serial communication with the computer
  Serial.print("To infinity and beyond!");  //test the serial connection
}

void forward() {
  rightMotor(255);
  leftMotor(255);
  delay(backupTime);
}

void reverse() {
  rightMotor(-255);
  leftMotor(-255);
  delay(backupTime);
}

void stopRobot() {
  rightMotor(0);
  leftMotor(0);
  delay(backupTime);
}

void pivotLeft() {
  rightMotor(255);
  leftMotor(0);
  delay(backupTime);
}

void pivotRight() {
  leftMotor(255);
  rightMotor(0);
  delay(backupTime);
}

void turnRight() {
  //make a large clockwise circle
  rightMotor(200);
  leftMotor(255);
  delay(backupTime);
}

void turnLeft() {
  /// make a small counterclockwise circle
  //the bigger the difference in velocities, the smaller the circle diameter
  //pivot makes the smallest circle possible, diameter of the circle is 2x width of the robot (radius = width robot)
  rightMotor(255);
  leftMotor(200);
  delay(backupTime);
}

void spinRight() {
  rightMotor(-255);      //maximum speed is 255, right backward
  leftMotor(255);      //maximum speed is 255, left forward
  delay(turnTime);
}

void spinLeft() {
  rightMotor(255);      //maximum speed is 255, right forward
  leftMotor(-255);      //maximum speed is 255, left backward
  delay(turnTime);
}

void Figure8() {
  //clockwise circle [large]
  circle(1);
  delay(200);   //adjust the delays so that the circle closes
  stopRobot();
  //counterclockwise circle [small]
  circle(-1);
  delay(200);   //adjust the delays so that the circle closes
  stopRobot();
}

void circle(int dir) {
  if (dir > 0) {
    //clockwise circle
    turnRight();
  }
  else {
    //counterclockwise circle
    turnLeft();
  }
  delay(1000);    //adjust the delay so that the circle closes
  stopRobot();
}
//robot moves in a square function
void square() {
  for (int i = 0; i < 4; i++) {
    forward();
    delay(1000);      //adjust delay for length of square sides
    stopRobot();
    spinRight();
    //pivotRight();
    delay(100);     //adjust delay for a 90 deg pivot or spin
    stopRobot();
  }
}

/********************************************************************************/
void loop()
{
  forward();
  delay(oneSecond);
  reverse();
  delay(oneSecond);
  stop();
  delay(oneSecond);
}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}


/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    //clockwise rotation, dir
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    //counterclockwise rotation, dir
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    //stop the motor
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  //set the wheel speed for either CW or CCW
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
  //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}
