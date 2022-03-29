#include <LiquidCrystal.h>

// Definerer Pins
#define WATER25 A0
#define WATER50 A1
#define WATER75 A2
#define WATER100 A3
#define MOTOR 8

// Definerer Variabler
unsigned long lastChange = 0;						// Brukes til å sjekke om endringene er for kjappe eller ikke
LiquidCrystal lcd(6, 7, 2, 3, 4, 5);				// Definerer LCD Displayet
String currentText;									// Brukes til å holde på teksten som vises på LCD Displayet
bool lastState[4] = {false, false, false, false};	// Brukes til å holde på siste status på sensorene

void setup() {
	lcd.begin(16, 2); // Initialiserer LCD Displayet

	// Setter pinsene til input/output
	pinMode(WATER25, INPUT);
	pinMode(WATER50, INPUT);
	pinMode(WATER75, INPUT);
	pinMode(WATER100, INPUT);
	pinMode(MOTOR, OUTPUT);
}

void loop() {
	// Leser av sensorene og pumpen
	bool water25 = digitalRead(WATER25);
	bool water50 = digitalRead(WATER50);
	bool water75 = digitalRead(WATER75);
	bool water100 = digitalRead(WATER100);
	bool pump = digitalRead(MOTOR);

	// Sjekker om det er en sensor feil
	if((!water25 && (water50 || water75 || water100)) || (!water50 && (water75 || water100)) || (!water75 && water100)) {
		if(pump) digitalWrite(MOTOR, LOW);
		display("Sensor feil");
	} else {
		// Sjekker at pumpen er på og at vann nivået er 100% for å så stoppe pumpen
		if(pump && water100) {
			digitalWrite(MOTOR, LOW);
			display("Pump stopped");
			delay(2000);
		// Sjekker at pumpen er av og at vann nivået er mindre en 25% for å så starte pumpen
		} else if(!pump && !water25) {
			digitalWrite(MOTOR, HIGH);
			display("Pump started");
			delay(2000);
		}

		// Sjekker om det er en endring i sensorene
		if(!pump && ((!water25 && lastState[0] != water25) || (!water50 && lastState[1] != water50) || (!water75 && lastState[2] != water75) || (!water100 && lastState[3] != water100))) {
			// Sjekker om endringene i sensorene er for kjappe for å så starte pumpen
			if(lastChange > millis()) {
				digitalWrite(MOTOR, HIGH);
				display("Unusual usage");
				delay(1000);
				display("Pump started");
				delay(1000);
			}

			// Oppdaterer lastChange
			lastChange = millis() + 2000;
		}

		// Oppdaterer lastState
		lastState[0] = water25;
		lastState[1] = water50;
		lastState[2] = water75;
		lastState[3] = water100;

		// Skriver ut vann nivået på LCD Displayet
		display(water100 ? "100%" : water75 ? "75%" : water50 ? "50%" : water25 ? "25%" : "0%");
	}

	delay(100);
}

// Funksjon fot å skrive ut på LCD Displayet
void display(String text) {
	// Sjekker om teksten er forskjellig fra den som er på LCD Displayet for å ungå unødvene oppdateringer
	if(text == currentText) return;
	currentText = text;

	// Clearer Displayer og skriver ut teksten
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Monitoring:");
	lcd.setCursor(0, 1);
	lcd.print(text);
}