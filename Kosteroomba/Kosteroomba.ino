#include <protothreads.h>

#define trig 2
#define echo 3
#define led 4

pt pt1, pt2; 

int dist = 0;

int GetDist(struct pt *pt) {
    PT_BEGIN(pt);

    dist = 0;
    digitalWrite(trig, 0);
    
    PT_SLEEP(pt, 2);
    digitalWrite(trig, 1);
    PT_SLEEP(pt, 15);
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

    PT_END(pt);
}

int BlinkLed(pt *pt) {
    PT_BEGIN(pt);
    
        blinkTime = millis();
        PT_WAIT_UNTIL(pt, millis() - blinkTime > 1000);
        digitalWrite(led, true);
        blinkTime = millis();
        PT_WAIT_UNTIL(pt, millis() - blinkTime > 1000);
        digitalWrite(led, false);    

    PT_END(pt);
}

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);
    PT_INIT(&pt1);
    PT_INIT(&pt2);
}

void loop() {
    GetDist(&pt1);
    BlinkLed(&pt2);
}
