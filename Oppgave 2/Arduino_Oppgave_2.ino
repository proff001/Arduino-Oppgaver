#define in 13
#define out 12

void setup() {
	pinMode(in, INPUT); 
	pinMode(out, OUTPUT);
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
	if(digitalRead(in) == 1) {
		fastBlink(out);
	} else {
		slowBlink(out);
	}
}