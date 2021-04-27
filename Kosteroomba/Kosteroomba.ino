#include "protothreads.h"

#define trig 8
#define echo 9

const int motors[2][3] = {
    {13, A4, A5},
    {12, A3, A2}
};

int dist = 0;

pt getDistance;
pt motor;

int getDist(struct pt* pt) {
    PT_BEGIN(pt);

    for(;;) {
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        

        const unsigned long duration= pulseIn(echo, HIGH);
        int distance = duration/29/2;
        if(duration==0){
        Serial.println("Warning: no pulse from sensor");
        } 
        else{
            Serial.print("distance to nearest object:");
            Serial.println(distance);
            Serial.println(" cm");
        }
        PT_YIELD(pt);
    }

    PT_END(pt);
}

int MotorStuff(struct pt* pt) {
    PT_BEGIN(pt);

    for(;;) {
        //This code  will turn Motor A clockwise for 2 sec.
        analogWrite(motors[0][1], 255);
        analogWrite(motors[0][2], 0);
        analogWrite(motors[1][1], 0);
        analogWrite(motors[1][2], 0);
        PT_SLEEP(pt, 2000);
        PT_YIELD(pt);

        //This code will turn Motor A counter-clockwise for 2 sec.
        analogWrite(motors[0][1], 0);
        analogWrite(motors[0][2], 255);
        analogWrite(motors[1][1], 0);
        analogWrite(motors[1][2], 0);
        PT_SLEEP(pt, 2000);
        PT_YIELD(pt);
        
        // This code will turn Motor B clockwise for 2 sec.
        analogWrite(motors[0][1], 0);
        analogWrite(motors[0][2], 0);
        analogWrite(motors[1][1], 255);
        analogWrite(motors[1][2], 0);
        PT_SLEEP(pt, 2000);
        PT_YIELD(pt);

        // This code will turn Motor B counter-clockwise for 2 sec.
        analogWrite(motors[0][1], 0);
        analogWrite(motors[0][2], 0);
        analogWrite(motors[1][1], 0);
        analogWrite(motors[1][2], 255);
        PT_SLEEP(pt, 2000);
        PT_YIELD(pt);
    }

    PT_END(pt);
}

void setup() {
    PT_INIT(&getDistance);
    PT_INIT(&motor);
    
    Serial.begin(9600);

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            pinMode(motors[i][j], OUTPUT);
        }
    }

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    digitalWrite(motors[0][0], 1);
    digitalWrite(motors[1][0], 1);
}

void loop() {
    PT_SCHEDULE(getDist(&getDistance));
    PT_SCHEDULE(MotorStuff(&motor));
}
