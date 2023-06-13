/* 
 Lily∞Bot 
 Sky Leilani 
 June 12th, 2023 
 
 This program is written to follow a path defined by using the pythagorean theorem. Made to be used on the LilyBot without any sensors, 
 so it will follow the calculated path, regardless of its actual position or the presence of obstacles. 
 */


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

void stopRobot() {
  setMotor(1, STOP, 0);
  setMotor(2, STOP, 0);
}

// Move the robot in the specified direction; default is forward
void move(int distance, int direction = FORWARD) {
  int speed = 255; // Adjust the speed of the motors as needed

  if (direction == FORWARD) {
    setMotor(1, FORWARD, speed);
    setMotor(2, FORWARD, speed);
  } else { // Must set second param to backward
    setMotor(1, BACKWARD, speed);
    setMotor(2, BACKWARD, speed);
  }

  delay(distance * 200); // ~ An inch on wood floor. Change multiplier to get the right distance
  stopRobot();
  delay(1000);
}



// Calculate the shortest path to the goal using Pythagorean's theorem
void gotogoal(int x, int y) {
  int currentX = 0; // Replace with the current X position of the robot
  int currentY = 0; // Replace with the current Y position of the robot

  // Calculate the change in X and Y directions
  int deltaX = x - currentX;
  int deltaY = y - currentY;

  // Calculate the diagonal distance 
  float hypotenuse = sqrt(deltaX * deltaX + deltaY * deltaY);

  // Calculate the turning angle using inverse tangent
  int angle = round(atan2(deltaY, deltaX) * 180.0 / PI);

  if (angle < 0) {
    angle += 360; // Adjust the angle to be positive
  }

  if (hypotenuse > 0) {
    pivotByAngle(angle); // Turn to the desired angle
    move(hypotenuse); // Move forward the calculated distance
  }
}

// Turn the robot by a specific angle
void pivotByAngle(int angle) {
  int turnTime = abs(angle) * 5; // Adjust the factor (5) to control the turning speed
  int motorSpeed = 255;

  if (angle > 0) { // Turn left
    setMotor(1, STOP, motorSpeed);
    setMotor(2, FORWARD, motorSpeed);
  } else { // Turn right
    setMotor(1, FORWARD, motorSpeed);
    setMotor(2, BACKWARD, motorSpeed);
  }

  delay(turnTime); // dictates the time the robot will turn for
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

  // ~72 degree turn 
  gotogoal(5, 15);
  stopRobot();
  delay(1000);

  
  // 45 degree turn
  gotogoal(12,12);
  stopRobot();
  delay(1000);

  // no turn
  gotogoal(15, 0);
  stopRobot();
  delay(1000);
  
}
