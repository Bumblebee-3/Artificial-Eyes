/*

  Copyright 2023 - Artificial Eyes

*/



/* ----- [MOTOR VARIABLES] ----- */

#define motorAF 10
#define motorAB 11
#define motorBF 12
#define motorBB 13


/* ----- [ULTRASONIC SENSOR VARIABLES] ----- */

#define usE1 2
#define usT1 3
#define usE2 4
#define usT2 5
#define usE3 6
#define usT3 7

long duration, cm, inches;


/* ----- [ULTRASONIC SENSOR METHODS] ----- */

long getDistance(int sensor = 1,String type = "cm"){
    int trig,echo;
    if( sensor == 1 ){
      trig = usT1;
      echo = usE1;
    }
    else if( sensor ==2 ){
      trig = usT2;
      echo = usE2;
    }
    else if( sensor == 3 ){
      trig = usT3;
      echo = usE3;
    }
    else {
      trig = usT1;
      echo = usE1;
    }
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    cm = (duration/2) / 29.1;
    inches = (duration/2) / 74;
    return ( type == "cm" ) ? cm : inches ;
}//USAGE: getDistance(ensor,unit);

/* ----- [MOTOR METHODS] ----- */

void goForward(){
    
}


/* ----- [SETUP] ----- */

void setup(){
  Serial.begin(9600);
  pinMode(motorAF,OUTPUT);
  pinMode(motorAB,OUTPUT);
  pinMode(motorBF,OUTPUT);
  pinMode(motorBB,OUTPUT);
  pinMode(usE1,INPUT);
  pinMode(usT1,OUTPUT);
  pinMode(usE2,INPUT);
  pinMode(usT2,OUTPUT);
  pinMode(usE3,INPUT);
  pinMode(usT3,OUTPUT);
}


/* ----- [MAIN LOOP] ----- */

void loop(){
  long sen1 = getDistance(1,"cm");
  long sen2 = getDistance(2,"cm");
  long sen3 = getDistance(3,"cm");
  Serial.println("Distance from sensor 1: "+String(sen1)+" cm");
  Serial.println("Distance from sensor 2: "+String(sen2)+" cm");
  Serial.println("Distance from sensor 3: "+String(sen3)+" cm");
  delay(5000);
}
