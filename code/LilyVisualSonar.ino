int ylwLED, redLED, trig, bluLED, grnLED, echo;
float dist, echotime;

// read sonar and return distance

int get_distance2() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  echotime = pulseInLong(echo, HIGH);
  dist = echotime / 148;
  return dist;
}

// turn of all LEDs
void all_LEDS_OM2() {
  digitalWrite(bluLED, HIGH);
  digitalWrite(grnLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(ylwLED, HIGH);
}

// turn of all LEDs
void all_LEDS_off2() {
  digitalWrite(bluLED, LOW);
  digitalWrite(grnLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(ylwLED, LOW);
}

void setup() {
  pinMode(ylwLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(bluLED, OUTPUT);
  pinMode(grnLED, OUTPUT);
  ylwLED = 10;
  redLED = 11;
  bluLED = 12;
  grnLED = 13;
  echo = 18;
  trig = 19;
  pinMode(trig, OUTPUT);
}

void loop() {
  if ((get_distance2()) < 4) {
    digitalWrite(ylwLED, HIGH);
  } else if ((get_distance2()) < 7) {
    digitalWrite(redLED, HIGH);
  } else if ((get_distance2()) < 10) {
    digitalWrite(bluLED, HIGH);
  } else {
    digitalWrite(grnLED, HIGH);
  }
  delay(500);
  all_LEDS_off2();
}
