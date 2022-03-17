#include <LiquidCrystal.h>

#define WATER25 A0
#define WATER50 A1
#define WATER75 A2
#define WATER100 A3
#define MOTOR 8

unsigned long lastChange = 0;
LiquidCrystal lcd(6, 7, 2, 3, 4, 5);
String currentText;
bool lastState[4] = {false, false, false, false};

void setup() {
	lcd.begin(16, 2);

	pinMode(WATER25, INPUT);
	pinMode(WATER50, INPUT);
	pinMode(WATER75, INPUT);
	pinMode(WATER100, INPUT);
	pinMode(MOTOR, OUTPUT);
}

void loop() {
	bool water25 = digitalRead(WATER25);
	bool water50 = digitalRead(WATER50);
	bool water75 = digitalRead(WATER75);
	bool water100 = digitalRead(WATER100);
	bool pump = digitalRead(MOTOR);

	if((!water25 && (water50 || water75 || water100)) || (!water50 && (water75 || water100)) || (!water75 && water100)) {
		if(pump) digitalWrite(MOTOR, LOW);
		display("Sensor feil");
	} else {
		if(pump && water100) {
			digitalWrite(MOTOR, LOW);
			display("Pump stopped");
			delay(2000);
		} else if(!pump && !water25) {
			digitalWrite(MOTOR, HIGH);
			display("Pump started");
			delay(2000);
		}

		if(!pump && (lastState[0] != water25 || lastState[1] != water50 || lastState[2] != water75 || lastState[3] != water100)) {
			if(lastChange > millis()) {
				digitalWrite(MOTOR, HIGH);
				display("Unusual usage");
				delay(1000);
				display("Pump started");
				delay(1000);
			}

			lastChange = millis() + 5000;
		}

		lastState[0] = water25;
		lastState[1] = water50;
		lastState[2] = water75;
		lastState[3] = water100;

		display(water100 ? "100%" : water75 ? "75%" : water50 ? "50%" : water25 ? "25%" : "0%");
	}

	delay(100);
}

void display(String text) {
	if(text == currentText) return;
	currentText = text;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Monitoring:");
	lcd.setCursor(0, 1);
	lcd.print(text);
}