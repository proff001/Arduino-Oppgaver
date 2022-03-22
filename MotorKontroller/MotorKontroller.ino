// 2 Dimensjonal Array for pinsene til L293D
const int motors[2][3] = {
	{13, A4, A5}, // Motor A (Rekefølge: Enable 1/2, Input 1, Input 2)
	{12, A3, A2} // Motor B (Rekefølge: Enable 3/4, Input 4, Input 3)
};

void setup() {
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 3; j++) {
			pinMode(motors[i][j], OUTPUT);
		}
	}

	digitalWrite(motors[0][0], 1);
	digitalWrite(motors[1][0], 1);
}

void loop() {
	//This code  will turn Motor A clockwise for 2 sec.
	analogWrite(motors[0][1], 255);
	analogWrite(motors[0][2], 0);
	analogWrite(motors[1][1], 0);
	analogWrite(motors[1][2], 0);
	delay(2000); 

	//This code will turn Motor A counter-clockwise for 2 sec.
	analogWrite(motors[0][1], 0);
	analogWrite(motors[0][2], 255);
	analogWrite(motors[1][1], 0);
	analogWrite(motors[1][2], 0);
	delay(2000);
	
	// This code will turn Motor B clockwise for 2 sec.
	analogWrite(motors[0][1], 0);
	analogWrite(motors[0][2], 0);
	analogWrite(motors[1][1], 255);
	analogWrite(motors[1][2], 0);
	delay(2000); 

	// This code will turn Motor B counter-clockwise for 2 sec.
	analogWrite(motors[0][1], 0);
	analogWrite(motors[0][2], 0);
	analogWrite(motors[1][1], 0);
	analogWrite(motors[1][2], 255);
	delay(2000);
}