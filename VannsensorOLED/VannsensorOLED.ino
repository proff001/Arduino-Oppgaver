#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // OLED Reset pin

#define WATER25 A0
#define WATER50 A1
#define WATER75 A2
#define WATER100 A3
#define MOTOR 3

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long lastChange = 0;
bool lastState[4] = { false, false, false, false };
bool highUsage = false;

void setup() {
	OLED.begin(SSD1306_SWITCHCAPVCC, 0x3D);

	pinMode(WATER25, INPUT);
	pinMode(WATER50, INPUT);
	pinMode(WATER75, INPUT);
	pinMode(WATER100, INPUT);
	pinMode(MOTOR, OUTPUT);

	OLED.display();
	delay(1000);
	OLED.clearDisplay();
}

void loop() {
	bool water25 = digitalRead(WATER25);
	bool water50 = digitalRead(WATER50);
	bool water75 = digitalRead(WATER75);
	bool water100 = digitalRead(WATER100);
	bool error = (!water25 && (water50 || water75 || water100)) || (!water50 && (water75 || water100)) || (!water75 && water100);
	bool pump = digitalRead(MOTOR);

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

	OLED.clearDisplay();
	OLED.setTextSize(1);
	OLED.setTextColor(WHITE);
	OLED.setCursor(0, 0);
	OLED.print(pump ? F("Pump: On") : F("Pump: Off"));
	OLED.setCursor(0, 15);
	OLED.print(error ? F("Error: Sensor Error") : highUsage ? F("Warning: High Usage") : F("No Error/Warning"));
	OLED.setCursor(((error ? lastState[3] : water100) || (error ? !lastState[0] : !water25)) ? 52 : 56, 30);
	OLED.print((error ? lastState[3] : water100) ? F("100%") : (error ? lastState[2] : water75) ? F("75%") : (error ? lastState[1] : water50) ? F("50%") : (error ? lastState[0] : water25) ? F("25%") : F("<25%"));
	OLED.drawRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 40, WHITE);
	OLED.fillRect(0, 40, SCREEN_WIDTH * ((error ? lastState[3] : water100) ? 1 : (error ? lastState[2] : water75) ? 0.75 : (error ? lastState[1] : water50) ? 0.5 : (error ? lastState[0] : water25) ? 0.25 : 0), SCREEN_HEIGHT - 40, WHITE);

	OLED.display();

	if(error) return;

	lastState[0] = water25;
	lastState[1] = water50;
	lastState[2] = water75;
	lastState[3] = water100;
}