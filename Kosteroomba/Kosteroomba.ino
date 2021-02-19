const int trig = 2;
const int echo = 3;

int dist = 0;

int time[3] = {0, 0, 0};

int currentTime = 0;

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    Serial.begin(9600);
}

void loop() {
    currentTime = millis();
    if(time[0] == 0 || time[0] <= currentTime) {
        dist = 0;
        digitalWrite(trig, 0);
        currentTime = millis();
        if(time[1] == 0 || time[1] <= currentTime) {
            
        }
        delayMicroseconds(15);
        digitalWrite(trig, 0);

        const unsigned long duration = pulseIn(echo, 1);
        dist = duration/29/2;
        if(duration == 0) {
            Serial.println("Warning: No pulse recived from sensor!");
        } else {
            Serial.print("Distance to nearest Object: ");
            Serial.print(dist);
            Serial.println(" cm");
        }
        digitalWrite(trig, 1);
    }
    time[0] == currentTime + 100;
}
