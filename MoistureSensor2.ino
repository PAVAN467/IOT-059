#include <Servo.h>
Servo motor;
int sensor = A0;
int motorPin = 9;

void setup(){
  pinMode(A0, INPUT);
  pinMode(motorPin, OUTPUT);
  motor.attach(motorPin);
  Serial.begin(9600);
}

void loop(){
  int sensedValue = analogRead(sensor);
    Serial.println(sensedValue);
  if(sensedValue>700){
    Serial.println("In loop");
    for(int i = 0; i <= 180; i++){
      //Serial.println(i);
      motor.write(i);
      delay(10);
    }
    for(int i = 180; i >= 0; i--){
      //Serial.println(i);
      motor.write(i);
      delay(10);
    }
  }
  

  delay(100);
}
