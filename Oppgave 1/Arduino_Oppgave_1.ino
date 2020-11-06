void setup() {
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  if (digitalRead(13) == 1) {
    digitalWrite(12, 1);
  } else {
    digitalWrite(12, 0);
  }
}
