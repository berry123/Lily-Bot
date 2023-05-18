/*
DaisyBot-PlayStation.ino
C.A.Berry S. Hyacinthe 3/12/23
This code will confirm that the PlayStation controller is working with the Daisy∞Bot
Hardware connections:
***TB6612 Motor Driver***
Arduino pin 7 PWMB
Arduino pin 6 BIN2
Arduino pin 5 BIN1
Arduino pin 4 AIN1
Arduino pin 3 AIN2
Arduino pin 2  PWMA
Arduino GND GND
Arduino 5V Vcc
Arduino VIN Vm
Left Motor Motor B
Right Motor Motor A

***LEDS***
yellow - 52
red - 53
blue - 50
green - 51

Buzzer - A3

***PlayStation****
PS2_DAT        13
PS2_CLK        12     
PS2_CMD        11  
PS2_SEL        10  

***Sonar***
Left Trigger	48	
Left Echo	49
Right Trigger	46
Right Echo	47
Back Trigger 	42
Back Echo 	43
Front Trigger	44
Front Echo	45

*/

#include <PS2X_lib.h>

//sonar pints
// sonar config
int trigPins[4] = { 44, 42, 48, 46 };  // front sonar, back sonar, left sonar, right sonar
int echoPins[4] = { 45, 43, 49, 47 };  // front sonar, back sonar, left sonar, right sonar
float echoTimes[4];
float dists[4];  // front distance, back distance, left distance, right distance

//LEDS/BUZZERS - test indicators
#define bluLED 50
#define grnLED 51
#define ylwLED 52
#define redLED 53


#define buzzer A3
#define RGBred A2
#define RGBgrn A1
#define RGBblu A0

//Motors
#define PWMB 7
#define BIN2 6
#define BIN1 5
#define AIN1 4
#define AIN2 3
#define PWMA 2

//PlayStation connections
#define PS2_DAT 13
#define PS2_CLK 12
#define PS2_CMD 11
#define PS2_SEL 10

// CONSTANTS
#define MID_X 128
#define MID_Y 128
#define MIN_SPIN_SPEED 50
#define TOL 5




// PIN CONFIGURATION
bool autonomous = false;

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;
int baudrate = 9600;

void setup() {
  setup_pins();
  //check connections
  Serial.begin(baudrate);
  Serial.println("Daisy∞Bot begin: ");
  Serial.println("Test wiring ");
  test_connections();
  //setup_controller();
}

void test_connections() {
  // Serial.println("play buzzer - pin A3");
  // tone(buzzer, 254, 500);
  // Serial.println("light yellow LED - pin 52");
  // digitalWrite(ylwLED, HIGH);
  // delay(1000);
  // ALL_LEDS_OFF();
  // Serial.println("light red LED - pin 53");
  // digitalWrite(redLED, HIGH);
  // delay(1000);
  // ALL_LEDS_OFF();
  // Serial.println("light blue LED - pin 50");
  // digitalWrite(bluLED, HIGH);
  // delay(1000);
  // ALL_LEDS_OFF();
  // Serial.println("light green LED - pin 51");
  // digitalWrite(grnLED, HIGH);
  // delay(1000);
  // ALL_LEDS_OFF();
  // Serial.println("move left wheel forward");
  // pivotL();
  // delay(1000);
  // stop();
  // Serial.println("move right wheel forward");
  // pivotR();
  // delay(1000);
  // stop();
  // Serial.println("move left wheel backward");
  // pivotBL();
  // delay(1000);
  // stop();
  // Serial.println("move right wheel backward");
  // pivotBR();
  // delay(1000);
  // stop();
  Serial.println("read front Sonar three times");
  for (int i = 0; i<10;i++){
    Serial.print(i);
    Serial.print(":\t");
    Serial.print(readSonar(1));
    delay(100);
  }
  Serial.println();
  // Serial.println("read back Sonar three times");

  // Serial.println("read left Sonar three times");

  // Serial.println("read right Sonar three times");
}

float readSonar(int i) {
  float echoTime;            //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;  //variable to store the distance calculated from the echo time
  Serial.println(i);
  Serial.println(trigPins[i]);
  Serial.println(echoPins[i]);
 
  digitalWrite(trigPins[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[i], LOW);

  echoTime = pulseIn(echoPins[i], HIGH);  //use the pulsein command to see how long it takes for the
   Serial.print("\techoTime: ");
   Serial.println(echoTime);

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance;              //send back the distance that was calculated
}

void getDistances() {

  //for each sonsar send out an ultrasonic pulse that's 10ms long
  for (int i = 0; i < 4; i++) {
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    /*
     use the pulsein command to see how long it takes for the 
     pulse to bounce back to the sonar and the calculate time
    */
    echoTimes[i] = pulseIn(echoPins[i], HIGH);

    /*
      calculate the distance of the object that reflected the 
      pulse (half the bounce time multiplied by the speed of sound)
    */
    dists[i] = echoTimes[i] / 148.0;
  }
}

void loop() {
  //   if (autonomous == true) {
  //     All_LEDS_ON2();
  //   }
  //   if (error = 3) {                      //DualShock Controller
  //     ps2x.read_gamepad(false, vibrate);  //read controller and set large motor to spin at 'vibrate' speed

  //     if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
  //       Serial.println("Start is being held");
  //     if (ps2x.Button(PSB_SELECT))
  //       Serial.println("Select is being held");


  //     if (ps2x.Button(PSB_PAD_UP)) {  //will be TRUE as long as button is pressed
  //       Serial.print("Up held this hard: ");
  //       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  //     }
  //     if (ps2x.Button(PSB_PAD_RIGHT)) {
  //       Serial.print("Right held this hard: ");
  //       Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  //     }
  //     if (ps2x.Button(PSB_PAD_LEFT)) {
  //       Serial.print("LEFT held this hard: ");
  //       Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  //     }
  //     if (ps2x.Button(PSB_PAD_DOWN)) {
  //       Serial.print("DOWN held this hard: ");
  //       Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  //     }


  //     vibrate = ps2x.Analog(PSAB_BLUE);  //this will set the large motor vibrate speed based on


  //     if (ps2x.ButtonPressed(PSB_RED))  //will be TRUE if button was JUST pressed
  //       Serial.println("Circle just pressed");

  //     if (ps2x.ButtonReleased(PSB_PINK))  //will be TRUE if button was JUST released
  //       Serial.println("Square just released");

  //     if (ps2x.NewButtonState(PSB_BLUE))  //will be TRUE if button was JUST pressed OR released
  //       Serial.println("X just changed");


  //     if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))  // print stick values if either is TRUE
  //     {
  //       Serial.print("Stick Values:");
  //       Serial.print(ps2x.Analog(PSS_LY), DEC);  //Left stick, Y axis. Other options: LX, RY, RX
  //       Serial.print(",");
  //       Serial.print(ps2x.Analog(PSS_LX), DEC);
  //       Serial.print(",");
  //       Serial.print(ps2x.Analog(PSS_RY), DEC);
  //       Serial.print(",");
  //       Serial.println(ps2x.Analog(PSS_RX), DEC);
  //     }

  //     int right_y = ps2x.Analog(PSS_RY);
  //     int left_y = ps2x.Analog(PSS_LY);


  //     if (right_y <= MID_Y + TOL) {
  //       //move forward
  //       int forward_speed = map(right_y, MID_Y + TOL, 0, 0, 255);
  //       rc_forward(forward_speed);
  //     } else if (right_y > MID_Y + TOL) {
  //       // move backwards
  //       int backward_speed = map(right_y, MID_Y + TOL, 255, 0, 255);
  //       rc_backward(backward_speed);
  //     }

  //     // SPINNING
  //     if (ps2x.Button(PSB_L2)) {
  //       int spin_speed = map(left_y, 255, 0, MIN_SPIN_SPEED, 255);
  //       Serial.println(spin_speed);
  //       rc_spinCCW(spin_speed);
  //     } else if (ps2x.Button(PSB_R2)) {
  //       int spin_speed = map(left_y, 255, 0, MIN_SPIN_SPEED, 255);
  //       rc_spinCW(spin_speed);
  //     }
  //   }
  //   if (ps2x.ButtonReleased(PSB_PINK) && !autonomous) {  //will be TRUE if button was JUST released
  //     autonomous = true;
  //     Serial.println("top:" + String(autonomous));
  //     delay(700);
  //   } else if (ps2x.ButtonReleased(PSB_PINK) && autonomous) {
  //     all_LEDS_OFF2();
  //     autonomous = false;
  //     delay(700);
  //   }


  //   delay(50);
}

/*WILL BE WRITTEN BY STUDENTS*/

void rc_backward(int speed) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, speed);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speed);
}

void rc_forward(int speed) {
  digitalWrite(grnLED, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speed);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speed);
  ALL_LEDS_OFF();
}


void rc_spinCW(int speed) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speed);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speed);
}


void rc_spinCCW(int speed) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, speed);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, speed);
}
//pivot left
//robot pivot function
void pivotL() {
  digitalWrite(AIN1, LOW);   //set pin 1 to low
  digitalWrite(AIN2, LOW);   //set pin 2 to high
  digitalWrite(BIN1, HIGH);  //set pin 1 to low
  digitalWrite(BIN2, LOW);   //set pin 2 to high
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 255);
}


//robot pivot function
void pivotBL() {
  digitalWrite(AIN1, LOW);   //set pin 1 to low
  digitalWrite(AIN2, LOW);   //set pin 2 to high
  digitalWrite(BIN1, LOW);   //set pin 1 to low
  digitalWrite(BIN2, HIGH);  //set pin 2 to high
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 255);
}

//pivot right
void pivotR() {
  digitalWrite(AIN1, HIGH);  //set pin 1 to low
  digitalWrite(AIN2, LOW);   //set pin 2 to high
  digitalWrite(BIN1, LOW);   //set pin 1 to low
  digitalWrite(BIN2, LOW);   //set pin 2 to high
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 0);
}

//pivot reverse right
void pivotBR() {
  digitalWrite(AIN1, LOW);   //set pin 1 to low
  digitalWrite(AIN2, HIGH);  //set pin 2 to high
  digitalWrite(BIN1, LOW);   //set pin 1 to low
  digitalWrite(BIN2, LOW);   //set pin 2 to high
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 0);
}
// move robot forward function
void move_forward() {
  digitalWrite(grnLED, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 255);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 255);
  ALL_LEDS_OFF();
}

// turn LEDS off function
void ALL_LEDS_OFF() {
  digitalWrite(bluLED, LOW);
  digitalWrite(grnLED, LOW);
  digitalWrite(ylwLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(RGBred, LOW);
  digitalWrite(RGBblu, LOW);
  digitalWrite(RGBgrn, LOW);
}

// all LEDS ON
void All_LEDS_ON() {
  digitalWrite(bluLED, HIGH);
  digitalWrite(grnLED, HIGH);
  digitalWrite(ylwLED, HIGH);
  digitalWrite(redLED, HIGH);
}

// stop robot function
void stop() {
  ALL_LEDS_OFF();
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

/*DO NOT EDIT CODE BELOW THIS POINT*/

void setup_pins() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(bluLED, OUTPUT);
  pinMode(grnLED, OUTPUT);
  pinMode(ylwLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(RGBgrn, OUTPUT);
  pinMode(RGBblu, OUTPUT);
  pinMode(RGBred, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void setup_controller() {

  error = ps2x.config_gamepad(PS2_DAT, PS2_CMD, PS2_SEL, PS2_CLK, true, true);  //GamePad(clock, command, attention, data, Pressures?, Rumble?)

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}