/*
  Lily∞Bot Basic Motion Control
  LilyBot-BasicMotion.ino
  Control 2 DC motors with TB6612 motor controller (https://www.adafruit.com/product/2448)
  This program will create low level motion control: forward, reverse, spin, turn, pivot, stop

  Carlotta A. Berry, PhD
  April 7, 2023
  Katie Collins
  5/11/23
  Hardware Connections:

    TB6612 Motor Driver
      Vmotor - voltage for the motors, not logic level (4.5-13.5V)
  Vcc - voltage for the logic levels (Arduinos, 5V)
  GND - shared logic and motor ground
    Arduino pin 8 AIN1
    Arduino pin 9 AIN2
    Arduino pin 10 PWMA
    Arduino pin 5 PWMB
    Arduino pin 6 BIN2
    Arduino pin 7 BIN1
    Arduino GND GND
    Arduino 5V Vcc
    Arduino VIN Vm
    Left Motor Motor A (Red, Black)
    Right Motor Motor B (Red, Black)

    Buzzer pin A3
    Blue LED pin 2
    Green LED pin 12
    Yellow LED pin 4
    Read LED pin 3
*/
#include "IRremote.h"

int ftreceiver = 11;  // Front IR Receiver

// /*-----( Declare objects )-----*/
IRrecv ftirrecv(ftreceiver);  // create instance of 'irrecv'
decode_results ftresults;     // create instance of 'decode_results'


//the left motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 8;   //control pin 1 on the motor driver for the left motor
const int AIN2 = 9;   //control pin 2 on the motor driver for the left motor
const int PWMA = 10;  //speed control pin on the motor driver for the left motor

//the right motor will be controlled by the motor B pins on the motor driver
const int PWMB = 5;  //speed control pin on the motor driver for the right motor
const int BIN2 = 6;  //control pin 2 on the motor driver for the right motor
const int BIN1 = 7;  //control pin 1 on the motor driver for the right motor


//robot behaviour variables
int moveTime = 500;    //amount of time robot will move
int robotSpeed = 150;  //robot speed


#define buzzerPin A3
#define bluLED 2
#define grnLED 12
#define ylwLED 4
#define redLED 3
int ledPins[4] = { 12, 2, 3, 4 };  //LED pins

//song variables
const int songLength = 18;
int tempo = 113;

//note for songs
char notes[songLength] = {
  'c', 'd', 'f', 'd', 'a', ' ', 'a', 'g', ' ', 'c', 'd', 'f', 'd', 'g', ' ', 'g', 'f', ' '
};

//beats for songs
int beats[songLength] = {
  1, 1, 1, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 1, 1, 4, 4, 2
};


int i, duration;
int j;
const int numNotes = 8;  // number of notes we're storing
char names[numNotes] = {
  'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'
};
int octave = 2;
int frequencies[numNotes] = {
  262 * octave - 1, 294 * octave - 1, 330 * octave - 1, 349 * octave - 1, 392 * octave - 1, 440 * octave - 1, 494 * octave - 1, 523 * octave - 1
};

/*runs only once at beginning******/
void setup() {
  Serial.begin(9600);  //start serial communication
  Serial.println("Lily∞Bot IR Remote Drive");
  ftirrecv.enableIRIn();  // Start the receiver
  configurePins();        //set pins as inputs and outputs
}

/*----( LOOP: RUNS CONSTANTLY )----*/
void loop() {
  if (ftirrecv.decode(&ftresults))  // have we received an IR signal?
  {
    Serial.println("front received");
    translateIR(ftresults);
    ftirrecv.resume();  // receive the next value
  }
  delay(100);
  //Serial.println("Back in loop");
} /* --(end main loop )-- */


/************************* HELPER FUNCTIONS *********************/
// set the pins as inputs and outputs
void configurePins() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(ftreceiver, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(bluLED, OUTPUT);
  pinMode(grnLED, OUTPUT);
  pinMode(ylwLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

//translate the IR signal into a robot ehavior based upon button pressed
void translateIR(struct decode_results results) {
  switch (results.value) {
    case 0xFFA25D:
      Serial.println("POWER");
      spin2();
      delay(moveTime);
      stop();
      break;
    case 0xFFE21D:
      Serial.println("FUNC/STOP");
      spin();
      delay(moveTime);
      stop();
      break;
    case 0xFF629D:
      Serial.println("VOL+");
      forward();
      delay(moveTime);
      stop();
      break;
    case 0xFF22DD:
      Serial.println("FAST BACK");
      turn();
      delay(moveTime);
      stop();
      break;
    case 0xFF02FD:
      Serial.println("PAUSE");
      play_song();
      Serial.println("Break");
      break;
    case 0xFFC23D:
      Serial.println("FAST FORWARD");
      turn2();
      delay(moveTime);
      stop();
      break;
    case 0xFFE01F:
      Serial.println("DOWN");
      pivot();
      delay(moveTime);
      stop();
      break;
    case 0xFFA857:
      Serial.println("VOL-");
      reverse();
      delay(moveTime);
      stop();
      break;
    case 0xFF906F:
      Serial.println("UP");
      pivot2();
      delay(moveTime);
      stop();
      break;
    case 0xFF6897:
      Serial.println("0");
      ALL_LEDS_ON();
      delay(moveTime);
      ALL_LEDS_OFF();
      break;
    case 0xFF30CF:
      Serial.println("1");
      ylwLedOn();
      delay(moveTime);
      ylwLedOff();
      break;
    case 0xFF18E7:
      Serial.println("2");
      redLedOn();
      delay(moveTime);
      redLedOff();
      break;
    case 0xFF7A85:
      Serial.println("3");
      bluLedOn();
      delay(moveTime);
      bluLedOff();
      break;
    case 0xFF10EF:
      Serial.println("4");
      grnLedOn();
      delay(moveTime);
      grnLedOff();
      break;
    case 0xFF9867: Serial.println("EQ"); break;
    case 0xFFB04F: Serial.println("ST/REPT");  break;
    case 0xFF38C7: Serial.println("5"); break;
    case 0xFF5AA5: Serial.println("6"); break;
    case 0xFF42BD: Serial.println("7"); break;
    case 0xFF4AB5: Serial.println("8"); break;
    case 0xFF52AD: Serial.println("9"); break;
    default:
      Serial.println(results.value);
      break;
  }            //end switch case
  delay(250);  // Do not get immediate repeat
}

// ************************************ Motor Functions *****************************


//robot stop function
void stop() {
  setRightMotorStop();
  setLeftMotorStop();
}

//robot forward function
void forward() {
  setRightMotorForward();
  setLeftMotorForward();
  //set motor speeds
  analogWrite(PWMA, abs(robotSpeed));  //set forward speed
  analogWrite(PWMB, abs(robotSpeed));  //set forward speed
}

//robot reverse function
void reverse() {
  setRightMotorBackward();
  setLeftMotorBackward();
  //set motor speeds
  analogWrite(PWMA, abs(robotSpeed));  //set reverse speed
  analogWrite(PWMB, abs(robotSpeed));  //set reverse speed
}

//robot pivot function
void pivot() {
  setRightMotorStop();
  setLeftMotorForward();
  //set motor speeds
  analogWrite(PWMB, abs(robotSpeed));  //set forward speed
}


//robot pivot function
void pivot2() {
  setRightMotorForward();
  setLeftMotorStop();
  //set motor speeds
  analogWrite(PWMA, abs(robotSpeed));  //set forward speed
}

//robot turn function
void turn() {
  setRightMotorForward();
  setLeftMotorForward();
  //set motor speeds
  analogWrite(PWMA, abs(robotSpeed));        //set forward speed
  analogWrite(PWMB, abs(0.7 * robotSpeed));  //set forward speed
}

//robot turn function
void turn2() {
  setRightMotorForward();
  setLeftMotorForward();
  //set motor speeds
  analogWrite(PWMA, abs(0.7 * robotSpeed));  //set forward speed
  analogWrite(PWMB, abs(robotSpeed));        //set forward speed
}

//robot spin function
void spin() {
  setRightMotorBackward();
  setLeftMotorForward();
  //set motor speeds
  analogWrite(PWMA, abs(robotSpeed));  //set reverse speed
  analogWrite(PWMB, abs(robotSpeed));  //set forward speed
}

//robot spin function
void spin2() {
  setRightMotorForward();
  setLeftMotorBackward();
  //set motor speeds
  analogWrite(PWMA, abs(robotSpeed));  //set forward speed
  analogWrite(PWMB, abs(robotSpeed));  //set reverse speed
}

void setRightMotorForward() {
  digitalWrite(AIN1, LOW);   //set pin 1 to low
  digitalWrite(AIN2, HIGH);  //set pin 2 to high
}

void setLeftMotorForward() {
  digitalWrite(BIN1, LOW);   //set pin 1 to low
  digitalWrite(BIN2, HIGH);  //set pin 2 to high
}

void setRightMotorBackward() {
  digitalWrite(AIN1, HIGH);  //set pin 1 to high
  digitalWrite(AIN2, LOW);   //set pin 2 to low
}


void setLeftMotorBackward() {
  digitalWrite(BIN1, HIGH);  //set pin 1 to high
  digitalWrite(BIN2, LOW);   //set pin 2 to low
}

void setRightMotorStop() {
  digitalWrite(AIN1, LOW);  //set pin 1 to low
  digitalWrite(AIN2, LOW);  //set pin 2 to low
}

void setLeftMotorStop() {
  digitalWrite(BIN1, LOW);  //set pin 1 to low
  digitalWrite(BIN2, LOW);  //set pin 2 to low
}



// ************************************ Buzzer Functions *****************************


// play the song
void play_song() {
  //  int i, duration;  //
  Serial.println("\t play song");
  ftirrecv.stop();
  for (i = 0; i < songLength; i++) {  // for loop is used to index through the arrays
    duration = beats[i] * tempo;      // length of note/rest in ms
    digitalWrite(ledPins[i % 4], HIGH);
    if (notes[i] == ' ')  // is this a rest?

      delay(duration);  // then pause for a moment
    else                // otherwise, play the note
    {
      if (i % 2 == 0) {  // robot spins a different direction on each note
        spin();          // robot spins along with the music
      } else {
        spin2();
      }
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration * 1.4);  // wait for tone to finish
      stop();
    }
    delay(tempo / 10);  // brief pause between notes
    ALL_LEDS_OFF();
  }
  ftirrecv.start();
}

//set the note frequencies
int frequency(char note) {
  for (j = 0; j < numNotes; j++)  // Step through the notes
  {
    if (names[j] == note)  // Is this the one?
    {
      return (frequencies[j]);  // Yes! Return the frequency and exit function.
    }
  }
  return (0);
}


// ************************************ LED Functions *****************************

// will turn on the green LED
void grnLedOn() {
  digitalWrite(grnLED, HIGH);
}

// will turn off green LED
void grnLedOff() {
  digitalWrite(grnLED, LOW);
}

// will turn on the yellow LED
void ylwLedOn() {
  digitalWrite(ylwLED, HIGH);
}

// will turn off yellow LED
void ylwLedOff() {
  digitalWrite(ylwLED, LOW);
}

// will turn on the red LED
void redLedOn() {
  digitalWrite(redLED, HIGH);
}

// will turn off red LED
void redLedOff() {
  digitalWrite(redLED, LOW);
}

// will turn on the blue LED
void bluLedOn() {
  digitalWrite(bluLED, HIGH);
}

// will turn off blue LED
void bluLedOff() {
  digitalWrite(bluLED, LOW);
}

// all LEDS OFF
void ALL_LEDS_OFF() {
  digitalWrite(bluLED, LOW);
  digitalWrite(grnLED, LOW);
  digitalWrite(ylwLED, LOW);
  digitalWrite(redLED, LOW);
}

// all LEDS ON
void ALL_LEDS_ON() {
  digitalWrite(bluLED, HIGH);
  digitalWrite(grnLED, HIGH);
  digitalWrite(ylwLED, HIGH);
  digitalWrite(redLED, HIGH);
}
