
//turn all the LEDS off
void allLedsOff () {
  for (int i = 0; i < 4 ; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

//get sonar distance
float getDistance(int *x, int *y)
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time
  int trigPin = *x;
  int echoPin = *y;
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
  //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
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
  //digitalWrite(redLED, HIGH);
  digitalWrite(AIN1, HIGH);                         //set pin 1 to high
  digitalWrite(AIN2, LOW);                          //set pin 2 to low
  digitalWrite(BIN1, HIGH);                         //set pin 1 to low
  digitalWrite(BIN2, LOW);                        //set pin 2 to high
  analogWrite(PWMA, abs(speed));    //set forward speed
  analogWrite(PWMB, abs(speed));    //set forward speed
}

//robot reverse function
void rev(int speed) {
  //digitalWrite(bluLED, HIGH);
  digitalWrite(AIN1, LOW);                         //set pin 1 to low
  digitalWrite(AIN2, HIGH);                        //set pin 2 to high
  digitalWrite(BIN1, LOW);                         //set pin 1 to low
  digitalWrite(BIN2, HIGH);                        //set pin 2 to high
  analogWrite(PWMA, abs(speed));    //set reverse speed
  analogWrite(PWMB, abs(speed));    //set reverse speed
}

//robot spin function
void spin(int speed, int dir) {
  //digitalWrite(grnLED, HIGH);
  if (dir > 0) { //spin right
    digitalWrite(AIN1, HIGH);                         //set pin 1 to low
    digitalWrite(AIN2, LOW);                        //set pin 2 to high
    digitalWrite(BIN1, LOW);                         //set pin 1 to low
    digitalWrite(BIN2, HIGH);                        //set pin 2 to high

  } else { //spin left
    digitalWrite(AIN1, LOW);                         //set pin 1 to low
    digitalWrite(AIN2, HIGH);                        //set pin 2 to high
    digitalWrite(BIN1, HIGH);                         //set pin 1 to low
    digitalWrite(BIN2, LOW);                        //set pin 2 to high
  }
  analogWrite(PWMA, abs(speed));    //set left wheel speed
  analogWrite(PWMB, abs(speed));    //set right wheel speed
}

//robot turn function
void turn(int speed, int dir) {
  //digitalWrite(redLED, HIGH);
  //digitalWrite(bluLED, HIGH);
  digitalWrite(AIN1, HIGH);                         //set pin 1 to low
  digitalWrite(AIN2, LOW);                        //set pin 2 to high
  digitalWrite(BIN1, HIGH);                         //set pin 1 to low
  digitalWrite(BIN2, LOW);                        //set pin 2 to high
  if (dir > 0) {//turn right
    analogWrite(PWMA, robotSpeed * 1.5);   //left wheel
    analogWrite(PWMB, robotSpeed * 0.5);   //right wheel
  }
  else {//turn left
    analogWrite(PWMA, robotSpeed * 0.5);   //left wheel
    analogWrite(PWMB, robotSpeed * 1.5);    //right wheel
  }
}

//robot pivot function
void pivot(int speed, int dir) {
  //digitalWrite(bluLED, HIGH);
  //digitalWrite(grnLED, HIGH);
  digitalWrite(AIN1, HIGH);                         //set pin 1 to low
  digitalWrite(AIN2, LOW);                        //set pin 2 to high
  digitalWrite(BIN1, HIGH);                         //set pin 1 to low
  digitalWrite(BIN2, LOW);                        //set pin 2 to high
  if (dir > 0) {//pivot right
    analogWrite(PWMA, abs(speed));  //left wheel
    analogWrite(PWMB, 0);           //right wheel
  }
  else { //pivot left
    analogWrite(PWMA, 0);          //left wheel
    analogWrite(PWMB, abs(speed)); //right wheel
  }
}

void randomWander(){      //function to move robot random forward and turn
  Serial.println("randomWander()");
  int randNumber = random(millis());    //generate a random number
  int distance = randNumber % 50;       //limit the values between 0 and 50 cm
  int angle = randNumber % 90;          //limit the values between 0 and 90 degrees
  Serial.print(distance);
  Serial.println(" deg\t");
  Serial.print(angle);
  Serial.print(" cm\t");
  fwd(robotSpeed);
  delay(distance);
  turn(angle,robotSpeed);
  delay(distance);
}
