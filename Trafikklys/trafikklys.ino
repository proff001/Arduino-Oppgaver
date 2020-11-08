int horizState = 0;
int vertState = 0;
int lightMode = 0;

const int lightState[4][4] = {
    {0, 1, 1},
    {0, 0, 1},
    {1, 1, 0},
    {1, 0, 1}
};

const int lights[4][3] = {
    {2, 3, 4},
    {5, 6, 7},
    {8, 9, 10},
    {11, 12, 13},
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
        } else {
            lightMode = horizState;
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