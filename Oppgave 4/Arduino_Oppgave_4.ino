#define red 13
#define green 12
#define blue 11

void setup() {
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
}

void none(int r, int g, int b, int time) {
	digitalWrite(r, 0);
	digitalWrite(g, 0);
	digitalWrite(b, 0);
	delay(time);
}

void sequence1(int r, int g, int b) {
	digitalWrite(r, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(g, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(b, 1);
	delay(500);
	none(r, g, b, 500);
	delay(500);
}

void sequence2(int r, int g, int b) {
	digitalWrite(b, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(g, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(r, 1);
	delay(500);
	none(r, g, b, 500);
	delay(500);
}

void sos(int r, int g, int b) {
	digitalWrite(r, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(b, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(g, 1);
	delay(500);
	none(r, g, b, 500);

	digitalWrite(r, 1);
	delay(1000);
	none(r, g, b, 1000);
	digitalWrite(b, 1);
	delay(1000);
	none(r, g, b, 1000);
	digitalWrite(g, 1);
	delay(1000);
	none(r, g, b, 1000);

	digitalWrite(r, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(b, 1);
	delay(500);
	none(r, g, b, 500);
	digitalWrite(g, 1);
	delay(500);
	none(r, g, b, 500);
}

void loop() {
	for(int i = 0; i < 3; i++) {
		sequence1(red, green, blue);
	}
	for(int i = 0; i < 3; i++) {
		sequence2(red, green, blue);
	}
	for(int i = 0; i < 3; i++) {
		sos(red, green, blue);
	}
}