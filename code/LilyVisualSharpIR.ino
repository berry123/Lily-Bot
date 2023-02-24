int ylwLED, redLED, bluLED, grnLED;
float val, distance, volts;

// read sonar and return distance

int get_distance2() {
  val = (analogRead(A0));
  volts = val * 5;
  volts = volts / 1024;
  distance = 29.988 * pow(volts, -1.173);
  distance = distance / 2.54;
  return distance;
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
  pinMode(A0, INPUT);
}

void loop() {
  if ((get_distance2()) < 4) {
    digitalWrite(ylwLED, HIGH);
  } else if ((get_distance2()) < 6) {
    digitalWrite(redLED, HIGH);
  } else if ((get_distance2()) < 8) {
    digitalWrite(bluLED, HIGH);
  } else {
    digitalWrite(grnLED, HIGH);
  }
  delay(100);
  all_LEDS_off2();
  delay(100);
}
