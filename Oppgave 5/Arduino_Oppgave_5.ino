const byte leds[4] = {11, 10, 9, 6};
const int button = 13;

void setup() {
    for(int i = 0; i <= 3; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    if(digitalRead(button) == 1) {
        for(int k = 0; k < 10; k++) {
            for(int i = 0; i <= 3; i++) {
                for(int j = 0; j <= 255; j++) {
                    analogWrite(leds[i], j);
                    delay(5);
                }

                for(int j = 255; j >= 0; j--) {
                    analogWrite(leds[i], j);
                    delay(5);
                }
            }
        }
    }
}

