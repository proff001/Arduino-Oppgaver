#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <protothreads.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // OLED Reset pin

#define WATER25 A0
#define WATER50 A1
#define WATER75 A2
#define WATER100 A3
#define MOTOR 3

#define HIGH_USAGE_LIMIT 2000 // Time betwen changes that will trigger high usage (milisecons)

pt updateDisplayThread;
pt getWaterLevelThread;

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long lastChange = 0;
unsigned long lastUpdate = 0;
bool lastState[4] = { false, false, false, false };
bool highUsage = false;
bool error = false;
bool pump = false;

void setup() {
	Serial.begin(9600);
	OLED.begin(SSD1306_SWITCHCAPVCC, 0x3D);

	pinMode(WATER25, INPUT);
	pinMode(WATER50, INPUT);
	pinMode(WATER75, INPUT);
	pinMode(WATER100, INPUT);
	pinMode(MOTOR, OUTPUT);

	PT_INIT(&updateDisplayThread);
	PT_INIT(&getWaterLevelThread);

	OLED.display();
	delay(1000);
	OLED.clearDisplay();
}

void loop() {
	unsigned long now = millis();
	OLED.clearDisplay();
	OLED.setTextSize(1);
	OLED.setTextColor(WHITE);
		// OLED.setCursor(56, 0);
	OLED.setCursor(0, 0);
	OLED.print("Frame time: " + String(lastUpdate/frameCount));
		// OLED.setCursor(0, 0);
		// OLED.print(pump ? F("Pump: On") : F("Pump: Off"));
		// OLED.setCursor(0, 15);
		// OLED.print(error ? F("Error: Sensor Error") : highUsage ? F("Warning: High Usage") : F("No Error/Warning"));
		// OLED.setCursor((lastState[3] || lastState[0]) ? 52 : 56, 30);
		// OLED.print(lastState[3] ? F("100%") : lastState[2] ? F("75%") : lastState[1] ? F("50%") : lastState[0] ? F("25%") : F("<25%"));
		// OLED.drawRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 40, WHITE);
		// OLED.fillRect(0, 40, SCREEN_WIDTH * (lastState[3] ? 1 : lastState[2] ? 0.75 : lastState[1] ? 0.5 : lastState[0] ? 0.25 : 0), SCREEN_HEIGHT - 40, WHITE);

	OLED.display();
	lastUpdate = millis();
	frameCount++;

	Serial.println(millis() - now);
	// PT_SCHEDULE(updateDisplay(&updateDisplayThread));
	// PT_SCHEDULE(getWaterLevel(&getWaterLevelThread));
}

unsigned long frameCount = 0;

int updateDisplay(struct pt* pt) {
	PT_BEGIN(pt);

	while(1) {
		unsigned long now = millis();
		OLED.clearDisplay();
		OLED.setTextSize(1);
		OLED.setTextColor(WHITE);
		// OLED.setCursor(56, 0);
		OLED.setCursor(0, 0);
		OLED.print("Frame time: " + String(lastUpdate/frameCount));
		// OLED.setCursor(0, 0);
		// OLED.print(pump ? F("Pump: On") : F("Pump: Off"));
		// OLED.setCursor(0, 15);
		// OLED.print(error ? F("Error: Sensor Error") : highUsage ? F("Warning: High Usage") : F("No Error/Warning"));
		// OLED.setCursor((lastState[3] || lastState[0]) ? 52 : 56, 30);
		// OLED.print(lastState[3] ? F("100%") : lastState[2] ? F("75%") : lastState[1] ? F("50%") : lastState[0] ? F("25%") : F("<25%"));
		// OLED.drawRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 40, WHITE);
		// OLED.fillRect(0, 40, SCREEN_WIDTH * (lastState[3] ? 1 : lastState[2] ? 0.75 : lastState[1] ? 0.5 : lastState[0] ? 0.25 : 0), SCREEN_HEIGHT - 40, WHITE);

		OLED.display();
		lastUpdate = millis();
		frameCount++;

		Serial.println(millis() - now);
		// PT_YIELD_UNTIL(pt, millis() - lastUpdate > 10);
	}

	PT_END(pt);
}

int getWaterLevel(struct pt* pt) {
	PT_BEGIN(pt);

	while(1) {
		bool water25 = digitalRead(WATER25);
		bool water50 = digitalRead(WATER50);
		bool water75 = digitalRead(WATER75);
		bool water100 = digitalRead(WATER100);

		error = (!water25 && (water50 || water75 || water100)) || (!water50 && (water75 || water100)) || (!water75 && water100);
		pump = digitalRead(MOTOR);

		if(error && pump) digitalWrite(MOTOR, LOW);
		if(!error && highUsage && !pump) digitalWrite(MOTOR, HIGH);
		if(!error && !pump && !water25) digitalWrite(MOTOR, HIGH);
		if(!error && pump && water100) digitalWrite(MOTOR, LOW);
		if(!error && !pump && ((!water25 && lastState[0] != water25) || (!water50 && lastState[1] != water50) || (!water75 && lastState[2] != water75) || (!water100 && lastState[3] != water100))) {
			if(lastChange > millis()) {
				digitalWrite(MOTOR, HIGH);
				highUsage = true;
			}

			lastChange = millis() + 2000;
		}

		pump = digitalRead(MOTOR);

		if(!error && !pump && highUsage) highUsage = false;
		if(!error) {
			lastState[0] = water25;
			lastState[1] = water50;
			lastState[2] = water75;
			lastState[3] = water100;
		}

		PT_YIELD(pt);
	}

	PT_END(pt);
}