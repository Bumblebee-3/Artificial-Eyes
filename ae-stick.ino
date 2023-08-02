/*---------- [LIBRARIES] ----------*/

#include <Servo.h>

/*---------- [LIBRARIES] ----------*/


Servo myservo;

/*---------- [VARIABLES] ----------*/

//Pin Variables
const int trigPin = 3;//UltraSonic Sensor pin (output)
const int echoPin = 7;//UltraSonic Sensor pin (input)
const int buzz = 11;//buzzer pin (output)
const int servo = 6;//servo data pin (output)
const int nodemcu = 12;

long duration, cm, inches;


/* ----- [ULTRASONIC SENSOR METHODS] ----- */
#define usE1 22
#define usT1 23
#define usE2 24
#define usT2 25
#define usE3 26
#define usT3 27
#define usE4 28
#define usT4 29


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
    else if( sensor == 4 ){
      trig = usT4;
      echo = usE4;
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




//Other Variables
long duration1, cm1;// sensor Data pins
int pos = 0;// Servo Position pins
String t = "inc";

/*---------- [VARIABLES] ----------*/


/*---------- [FUNCTIONS] ----------*/

/*----- [Rings] -----*/

//ring one (not very close)
void ring1(){
  digitalWrite(buzz,HIGH);
  delay(1000);
  digitalWrite(buzz,LOW);
  delay(1000);
}

//ring 2 (close)
void ring2(){
  digitalWrite(buzz,HIGH);
  delay(500);
  digitalWrite(buzz,LOW);
  delay(500);
  digitalWrite(buzz,HIGH);
  delay(500);
  digitalWrite(buzz,LOW);
  delay(500);
}

//ring 3 (very close)
void ring3(){
  digitalWrite(buzz,HIGH);
  delay(2000);
}

//no tone (not in danger)
void notone(){
  digitalWrite(buzz,LOW);
}

/*----- [Rings] -----*/


//sensor code
boolean sensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH);
  cm1 = (duration1/2) / 29.1;
  Serial.print(cm1);
  Serial.println(" cm");
  if (cm1<=80 && cm1>50){
    ring1();
    Serial.println("RING1");
    return false;
  }

  else if (cm1<=50 && cm1>30) {
    ring2();
    Serial.println("RING2");   
    return false; 
  }

  else if (cm1<=30){
    ring3();
    Serial.println("RING3");
    return false;
  }
  else {
    notone();
    return true;
  }
}

//main code (servo motor)
void initialize(){
  Serial.println("Running one loop");
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    myservo.write(pos);
    if(pos%10==0){sensor();}//running/calling the "sensor" code/function
    //delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    if(pos%10==0){sensor();}//running/calling the "sensor" code/function
    //delay(15);
  }
}

// void setup code in a function
void setupCode(){
  //attaching servo 
  myservo.attach(servo);
  //Declaring the pin modes (Input or Output)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz,OUTPUT);
  Serial.println("initialized");
}

/*---------- [FUNCTIONS] ----------*/



/*---------- [VOID SETUP]-(Runs only once i.e. at the starting of the program) ----------*/
void setup() { 
    Serial.begin(9600);
    setupCode();
}

/*---------- [VOID SETUP]-(Runs only once i.e. at the starting of the program) ----------*/


/*---------- [VOID LOOP] - {Main Code} (runs throughout) ----------*/
void loop(){
  if(sensor()==false){Serial.println("object detected");}
  else{
    if(digitalRead(nodemcu)==HIGH){
      float sen1 = getDistance(1,"cm");
      float sen2 = getDistance(2,"cm");
      float sen3 = getDistance(3,"cm");
      float sen4 = getDistance(4,"cm");
      Serial.println(String(sen1)+"/"+String(sen2)+"/"+String(sen3)+"/"+String(sen4));
    }
    if(t == "inc"){
      myservo.write(pos);
      pos+=10;
      if(pos==180){t="dec";}
    }
    else if(t=="dec"){
      myservo.write(pos);
      pos-=10;
      if(pos==0){t="inc";};
    }
  }
  delay(500);
}


/*---------- [VOID LOOP] - {Main Code} (runs throughout) ----------*/
