// Offsets are used to adjust speed of each motor in the case of speed differences between wheels
const int offsetA = 0;
const int offsetB = 0;

// motor A (left)
#define AIN1 8
#define AIN2 9

// motor B (right)
#define BIN1 13
#define BIN2 12

// speed pins
#define PWMA 10
#define PWMB 11

// Motor directions
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4
#define STOP 5

// set motor direction and speed functionality for each individual motor
void setMotor(int motor, int direction, int speed) {

  // motor A functionality (left motor)
  if (motor == 1) {
    if (direction == FORWARD) {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
    }
    else if (direction == BACKWARD) {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
    }
    else if (direction == STOP) {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
    }
    if (speed >= 0 && speed <= 255) {
      analogWrite(PWMA, speed + offsetA);
    } else {
      Serial.println("Err: Please choose a speed value between 0 and 255.");
    }
  }

  // motor B functionality (right motor)
  else if (motor == 2) {
    if (direction == FORWARD) {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }
    else if (direction == BACKWARD) {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    else if (direction == STOP) {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    }
    if (speed >= 0 && speed <= 255) {
      analogWrite(PWMB, speed + offsetB);
    } else {
      Serial.println("Err: Please choose a speed value between 0 and 255.");
    }
  }
}

// stop both motors
void stopRobot() {
  setMotor(1, STOP, 0);
  setMotor(2, STOP, 0);
}

// stationary pivot
void pivot(int direction, int speed) {
  if (direction == LEFT) {
    setMotor(1, STOP, speed);
    setMotor(2, FORWARD, speed);
  } else { // Default: stationary right pivot
    setMotor(1, FORWARD, speed);
    setMotor(2, STOP, speed);
  }
}

// gradual, curved pivot
void slightPivot(int direction, int speedLeft, int speedRight) {
  if (direction == LEFT) {
    setMotor(1, FORWARD, speedRight);
    setMotor(2, FORWARD, speedLeft);
  } else { // Default: gradual right pivot
    setMotor(1, FORWARD, speedLeft);
    setMotor(2, FORWARD, speedRight);
  }
}

// Move the robot in the specified direction; default is forward
void move(int speed, int direction = FORWARD) {
  if (direction == FORWARD) {
    setMotor(1, FORWARD, speed);
    setMotor(2, FORWARD, speed);
  } else { // Must set second param to backward
    setMotor(1, BACKWARD, speed);
    setMotor(2, BACKWARD, speed);
  }
}

// Move the robot in a square 
void square(int speed) {
  for (int i = 0; i < 4; i++) {
    pivot(LEFT, speed + 10);
    delay(1000);

    move(speed);
    delay(1000);
  }
  stopRobot();
  delay(2000);
}

// Move the robot in a circle
void circle(int direction, int speedA, int speedB) {
  if (direction == LEFT) {
    slightPivot(LEFT, speedA, speedB);
  } else 
  // default is clockwise 
  {
    slightPivot(RIGHT, speedA, speedB);
  }
}

// Move the robot in a figure-eight
void infinity() {
  circle(RIGHT,185,100);
  delay(4500); 
  stopRobot();
  delay(500);
  circle(LEFT,185,100); 
  delay(5500);
  stopRobot();
  delay(1000);
}

// Initialize motor control pins as outputs
void setup() {
  // motor A
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  // motor B
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // speed for motor A & motor B
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

// Repeat function testing
void loop() {
  circle(128, 80);
  stopRobot(); 
  delay(1000);
  square(128);
  stopRobot(); 
  delay(1000); 
  infinity(); 
  delay(1000);
}
