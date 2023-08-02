#define usE1 10
#define usT1 9
#define usE2 12
#define usT2 11
#define usE3 4
#define usT3 3
int IN1_A = 5;
int IN2_A = 6;
int IN1_B = 7;
int IN2_B = 8;

int uTBOB;
String str;

double duration, cm;

double getDistance(int sensor = 1, String type = "cm") {
    int trig, echo;
    if (sensor == 1) {
        trig = usT1;
        echo = usE1;
    } else if (sensor == 2) {
        trig = usT2;
        echo = usE2;
    } else if (sensor == 3) {
        trig = usT3;
        echo = usE3;
    } else {
        trig = usT1;
        echo = usE1;
    }

    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    cm = (duration / 2) / 29.1;
    return cm;
}
void stopMotors(){
    digitalWrite(IN1_A,LOW);
    digitalWrite(IN1_B,LOW);
    digitalWrite(IN2_A,LOW);
    digitalWrite(IN2_B,LOW);  
}

void forwardForever() {
    stopMotors();
    digitalWrite(IN1_A,HIGH);
    digitalWrite(IN1_B,HIGH);
}
void backwardForever() {
    stopMotors();
    digitalWrite(IN2_A,HIGH);
    digitalWrite(IN2_B,HIGH);
}
void leftTurn(int del = 500) {
    stopMotors();
    digitalWrite(IN1_B,HIGH);
    digitalWrite(IN2_A,HIGH);
    delay(del);
    digitalWrite(IN1_B,LOW);
    digitalWrite(IN2_A,LOW);
    stopMotors();
}
    
void rightTurn(int del=500) {
    stopMotors();
    digitalWrite(IN1_A,HIGH);
    digitalWrite(IN2_B,HIGH);
    delay(del);
    
    digitalWrite(IN1_A,LOW);
    digitalWrite(IN2_B,LOW);
    stopMotors();
}


void uTurn(int uTBOB) {
    if (uTBOB == 0) {
        backwardForever();
        delay(750);
        stopMotors();
        delay(500);
        rightTurn(500);
        delay(500);
        forwardForever();
        delay(500);
        stopMotors();
        rightTurn();
    } else {
        backwardForever();
        delay(500);
        stopMotors();
        leftTurn();
        forwardForever();
        delay(500);
        stopMotors();
        leftTurn();
    }
}
void setup() {
    Serial.begin(9600);

    pinMode(usE1, INPUT);
    pinMode(usT1, OUTPUT);
    pinMode(usE2, INPUT);
    pinMode(usT2, OUTPUT);
    pinMode(usE3, INPUT);
    pinMode(usT3, OUTPUT);
    pinMode(IN1_A,OUTPUT);
    pinMode(IN2_A,OUTPUT);
    pinMode(IN1_B,OUTPUT);
    pinMode(IN2_B,OUTPUT);
    Serial.println("Initializing Bot");

    double frontDist = getDistance(1, "cm");
    double leftDist = getDistance(2, "cm");
    double rightDist = getDistance(3, "cm");

    if (leftDist > rightDist) {
        uTBOB = 1;
        Serial.println("help");
    } else if (leftDist == rightDist) {
        Serial.println("shit");
    } else {
        uTBOB = 0;
        Serial.println("no help");
    }
    Serial.println("uTBOB:" + String(uTBOB));
    /*forwardForever();
    delay(1000);
    stopMotors();*/
    
    //leftTurn();
    uTurn(0);
}

void loop() {
    delay(1000);

    double frontDist = getDistance(1, "cm");
    double leftDist = getDistance(2, "cm");
    double rightDist = getDistance(3, "cm");
    Serial.println("frontDist:" + String(frontDist) + "\nleftDist:" +
                   String(leftDist) + "\nrightDist:" + String(rightDist));
    /*
    

    if (frontDist <= 5) {
        motor.stop();
        //motor.stopB();
        uTurn(uTBOB);
        str += "\n";
    } else {
        forwardForever();
        if (leftDist <= 10 || rightDist <= 10) {
            str += "1";
        } else {
            str += "0";
        }
    }
    Serial.println("---\n" + str + "\n---");*/
}
