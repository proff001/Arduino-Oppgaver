const int in = 13;
const int out = 12;

void setup() {
  pinMode(in, INPUT); 
  pinMode(out, OUTPUT);
  Serial.begin(9600);
}

void fastBlink(int pin) {
  digitalWrite(pin, 1);
  delay(250);
  digitalWrite(pin, 0);
  delay(250);
}

void slowBlink(int pin) {
  digitalWrite(pin, 1);
  delay(1000);
  digitalWrite(pin, 0);
  delay(1000);
}

void loop() {
  Serial.println(digitalRead(in));
  if(digitalRead(in) == 1) {
    fastBlink(out);
  } else {
    slowBlink(out);
  }
}