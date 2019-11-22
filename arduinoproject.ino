
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
//#define EspSerial Serial1
#define ESP8266_BAUD 9600
SoftwareSerial ESPserial(2, 3);
ESP8266 wifi(&ESPserial);

int MQ5=A0; 
int MQ135=A1;
float MQ135value;
float MQ5value;
float rsro;
char auth[] = "kGcM_L4VNDE3VD3xp_OU1GhjQLbLHNNt";
char ssid[] = "POCO F1";
char pass[] = "pavan123";
float RS_air;
float R0=20.0;
float ratio=0.0;


BlynkTimer timer;
float uptimeCounter;

// This function will run every time Blynk connection is established
BLYNK_CONNECTED() {
  //get data stored in virtual pin V0 from server
  Blynk.syncVirtual(V5);
}
float CO(float r){
  return -(r-4.0)*9000;
}
float alcohol(float r){
  return -((r-3.0)*25000)/9;
}
float LPG(float r){
  return -(r-0.9)*1500;
}
float CH_4(float r){
  return -((r-1.5)*80000)/13;
}
float h_2(float r){
  return -((r-1.9)*35000)/13;
}
void increment() {
  uptimeCounter=ratio;

  //storing int in V0 pin on server
  Blynk.virtualWrite(V5, CO(ratio))
  ;
  Blynk.virtualWrite(V4, alcohol(ratio));
  
 
}

float map_value(float value,float input_start,float input_end,float output_start,float output_end){
  float output = (float)(output_start + ((output_end - output_start) / (input_end - input_start)) * (value - input_start));
  return output;
}
void setup()
{
  Serial.begin(9600);    
  ESPserial.begin(9600); 
  Serial.println("Ready");
  ESPserial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);  
  
  timer.setInterval(1000L, increment);
}
 
void loop()
{   Blynk.run();
    timer.run();
   
    int count = 1;
    float avg;
    while(count<=10){
        MQ5value= MQ5value+analogRead(A0);
        count = count+1;
        delay(300);
 
    }
    avg = MQ5value/10;
   
    RS_air = (5.0-(avg/1024.0))/(avg/1024.0); // omit *RL
    Serial.print("MQ5value = ");
    Serial.println(avg);
    ratio = RS_air/R0;
    Serial.print("RS_gas/R0: ");
    Serial.println(ratio);
   // Serial.println(CO(ratio));
    Serial.println("Alcohol: ");
    Serial.println(alcohol(ratio));
    delay(100);
   // rsro=map_value(MQ5value,0,1023,0.1,10);
   // Serial.println(rsro);
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if(ESPserial.available()) 
    { 
      Serial.write(ESPserial.read());  
    }

 
    // listen for user input and send it to the ESP8266
    if(Serial.available())       
    {  ESPserial.write( Serial.read());  
    }
    delay(500);
}
