int horizState = 0;
int vertState = 0;
int lightMode = 0;
int walkMode = 0;

const int lightState[4][4] = {
	{0, 1, 1}, // Rødt
	{0, 0, 1}, // Rødt gult
	{1, 1, 0}, // Grønnt
	{1, 0, 1}  // Gult
};

const int walkLightState[2][2] = {
	{0, 1}, // Fotgjengerovergang Rødt
	{1, 0} // Fotgjengerovergang Grønnt
};

const int walkLights[2][2] = {
	{A0, A1}, // Fotgjengerovergang Øst
	{A2, A3} // Fotgjengerovergang Nord
};

const int lights[4][3] = {
	{2, 3, 4}, // Sør
	{5, 6, 7}, // Nord
	{8, 9, 10}, // Vest
	{11, 12, 13}, // Øst
};

const float time[4] = {
	0.5, // Tid fra rødt til rødt gult
	2, // Tid fra rødt gult til grønnt
	6, // Tid fra grønnt til gult
	2.5  // Tid fra gult til rødt
};

void setup() {
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 4; j++) {
			pinMode(lights[i][j], OUTPUT);
		}
	}
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			pinMode(walkLights[i][j], OUTPUT);
		}
	}
}

void Trafikklys() {
	for(int i = 0; i < int((sizeof(lightState))/(sizeof(*lightState))); i++) {
		vertState = i;
		horizState = 0;
		UpdateLEDs(time[i] * 1000);
	}
	for(int i = 0; i < int((sizeof(lightState))/(sizeof(*lightState))); i++) {
		vertState = 0;
		horizState = i;
		UpdateLEDs(time[i] * 1000);
	}
}

void UpdateLEDs(int time) {
	for(int i = 0; i < int((sizeof(lights))/(sizeof(lights[0]))); i++) {
		lightMode = 0;
		if (i <= 1) {
			lightMode = vertState;
			if (vertState != 2) {
				for(int j = 0; j < 2; j++) {
					digitalWrite(walkLights[0][j], walkLightState[0][j]);
				}
			} else {
				for(int j = 0; j < 2; j++) {
					digitalWrite(walkLights[0][j], walkLightState[1][j]);
				}
			}
		} else {
			lightMode = horizState;
			if (horizState != 2) {
				for(int j = 0; j < 2; j++) {
					digitalWrite(walkLights[1][j], walkLightState[0][j]);
				}
			} else {
				for(int j = 0; j < 2; j++) {
					digitalWrite(walkLights[1][j], walkLightState[1][j]);
				}
			}
		}
		for(int j = 0; j < 3; j++) {
			digitalWrite(lights[i][j], lightState[lightMode][j]);
		}
	}

	delay(time);
}

void loop() {
	Trafikklys();
}