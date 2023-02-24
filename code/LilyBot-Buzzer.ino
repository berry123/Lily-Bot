/*
  Lily∞Bot
  LilyBot-Buzzer.ino
  Carlotta A. Berry, PhD
  FEBRUARY 5, 2023

  This program will use the SparkFun Inventor's Kit version 3.0 buzzer code to show how to
  play music on the Lily∞Bot (see https://www.sparkfun.com/sikcode)


*/

//state LEDs
const int ledPins[4] = {4, 5, 6, 7 };
const int ylwLED = 4;
const int redLED = 5;
const int bluLED = 6;
const int grnLED = 7;


const int switchPin = 2;      //robot on-off switch
const int buzzerPin = 3;       //buzzer pin
const int photoresistor = A0;  //photoresistor pin


//the left motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 8;  //control pin 1 on the motor driver for the left motor
const int AIN2 = 9;  //control pin 2 on the motor driver for the left motor
const int PWMA = 10;  //speed control pin on the motor driver for the left motor

//the right motor will be controlled by the motor B pins on the motor driver
const int PWMB = 11;  //speed control pin on the motor driver for the right motor
const int BIN1 = 12;  //control pin 1 on the motor driver for the right motor
const int BIN2 = 13;  //control pin 2 on the motor driver for the right motor


//robot behaviour variables
int moveTime = 2000;   //amount of time robot will move
int robotSpeed = 100;  //robot speed

//song variables
const int songLength = 18;
int tempo = 150;

char notes[songLength] = {
  'c', 'd', 'f', 'd', 'a', ' ', 'a', 'g', ' ', 'c', 'd', 'f', 'd', 'g', ' ', 'g', 'f', ' '
};

int beats[songLength] = {
  1, 1, 1, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 1, 1, 4, 4, 2
};


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
  // set buzzer as an output
  pinMode(buzzerPin, OUTPUT);

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
    delay(1000);
  }
  Serial.println();
  for (int i = 4; i > -1; i--) {
    //Serial.print(i);
    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }
  Serial.print("Daisy∞bot begin");  //print start message
}

/********************************************************************************/
void loop() {
  int on = digitalRead(switchPin);
  Serial.print(" on = ");
  Serial.println(on);
  if (on == 1) {
    play_song();
  }
  if (on == 0) {
    Serial.println("Robot Off");
    stop();
  }
}
/************************* BUZZER FUNCTIONS *************************************/
// play the song
void play_song() {
  int i, duration;  //
  Serial.print("\t play song");

  for (i = 0; i < songLength; i++)  // for loop is used to index through the arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms
    digitalWrite(ledPins[i%4],HIGH);
    if (notes[i] == ' ')  // is this a rest?
      delay(duration);    // then pause for a moment
    else                  // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);  // wait for tone to finish
    }
    delay(tempo / 10);  // brief pause between notes
    allLedsOff();
  }
}

//set the note frequencies
int frequency(char note) {
  int i;
  const int numNotes = 8;  // number of notes we're storing
  char names[numNotes] = {
    'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'
  };
  int frequencies[numNotes] = {
    262, 294, 330, 349, 392, 440, 494, 523
  };

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)  // Is this the one?
    {
      return (frequencies[i]);  // Yes! Return the frequency and exit function.
    }
  }
  return (0);
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
