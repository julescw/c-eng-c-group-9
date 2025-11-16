#include "AFMotor_R4.h"

// initializing sensor pin
int sensorPin = 2; 
int sensorValue = 0;

// helper functions for moving logic
bool moveforward(void);
int searchposition(void);
void turnright(void);
void turnleft(void);
void stop(void);

// initializing motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);

// setup function for arduino IDE
void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600); 

  // Set initial speed and release motor
  motor3.setSpeed(50);
  motor3.run(RELEASE);
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
}

void loop(){
  sensorValue = digitalRead(sensorPin);

  if(sensorValue == LOW) {
    // sensor detects white surface
    int newdir = searchposition();
    if(newdir == 0){
        turnleft();
    }
    else if(newdir == 1){
        turnright();
    }
    else{
        searchposition();
    }
  } else {
    // sensor detects black line
    moveforward();
  }

  delay(200);
}

void moveforward(void){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(1000); 
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(1000);
}

int searchposition(void){
  int found = -1; // left = 0, right = 1, not found = -1
  int steps = 50;
  motor3.run(FORWARD);

  for (int i = 0; i < steps; i++) {
    motor3.run(FORWARD);           
    delay(20); 
    sensorValue = digitalRead(sensorPin);                   
    if (sensorValue == HIGH) {       
      found = 1;                 
    }
  } 
  for (int i = 0; i < steps; i++) {
    motor3.run(BACKWARD);           
    delay(20); 
  }
  if(found){
    return found;
  }
  else{
    for (int i = 0; i < steps; i++) {
    motor3.run(BACKWARD);           
    delay(20); 
    sensorValue = digitalRead(sensorPin);                   
    if (sensorValue == HIGH) {       
      found = 0;                 
      }
    }
  for (int i = 0; i < steps; i++) {
    motor3.run(FORWARD);           
    delay(20); 
    }
  }
  motor3.run(FORWARD);
  return found;
}

void turnright(void){
    motor1.run(FORWARD);
    delay(1000); 
    motor1.run(RELEASE);
}

void turnleft(void){
    motor2.run(FORWARD);
    delay(1000); 
    motor2.run(RELEASE);
}
