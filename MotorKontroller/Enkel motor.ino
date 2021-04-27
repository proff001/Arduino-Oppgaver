// Array for pinsene til L293D
const int motors[3] = {
    13, A4, A5, // Motor (Rekefølge: Enable 1/2, Input 1, Input 2)
};

void setup() {
    for(int i = 0; i < 3; i++) {
        pinMode(motors[i], OUTPUT);
    }

    digitalWrite(motors[0], 1);
}

void loop() {
    //This code  will turn Motor A clockwise for 2 sec.
    analogWrite(motors[1], 255);
    analogWrite(motors[2], 0);
    delay(2000); 

    //This code will turn Motor A counter-clockwise for 2 sec.
    analogWrite(motors[1], 0);
    analogWrite(motors[2], 255);
    delay(2000);
}
