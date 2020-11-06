const int red[4] = {A0, A3, 6, 11};
const int green[4] = {A1, A4, 5, 10};
const int yellow[4]= {A2, A5, 3, 9};

void setup() {
    for(int i = 0; i <= 3; i++) {
        pinMode(red[i], OUTPUT);
    }
    for(int i = 0; i <= 3; i++) {
        pinMode(green[i], OUTPUT);
    }
    for(int i = 0; i <= 3; i++) {
        pinMode(yellow[i], OUTPUT);
    }
}

void setColor(int cross, char color) {
    if(cross % 2 != 0) {
        if(color == 'r') {
            for(int i = 0; i <= 3; i++) {
                if(i % 2 != 0) {
                    digitalWrite(red[i], true);
                    digitalWrite(green[i], false);
                    digitalWrite(yellow[i], false);
                } else {
                    digitalWrite(red[i], false);
                    digitalWrite(red[i], true);
                    digitalWrite(red[i], true);
                }
            }
        } else if(color == 'g') {
            for(int i = 0; i <= 3; i++) {
                if(cross % 2 != 0) {
                    
                }
                if(i % 2 != 0) {
                    digitalWrite(red[i], true);
                    digitalWrite(green[i], false);
                    digitalWrite(yellow[i], false);
                } else {
                    digitalWrite(red[i], false);
                    digitalWrite(red[i], true);
                    digitalWrite(red[i], true);
                }
            }
        }
    }
}

void loop() {
    
}