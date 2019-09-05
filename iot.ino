#include<SoftwareSerial.h>
int sensorPin=A0;
int sensorvalue=0;
int led=9;
int buzzer=12;

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorvalue=analogRead(sensorPin);
  Serial.println(sensorvalue);
  if(sensorvalue<100)
  {
    Serial.println("fire detected");
    Serial.print("LED ON");
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(1000);
  }


    digitalWrite(buzzer,LOW);
    digitalWrite(led,LOW);
    delay(sensorvalue);
    
}
    
