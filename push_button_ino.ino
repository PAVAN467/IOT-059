int buttonRead=0;

void setup()
{
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
}

void loop()
{
  buttonRead=digitalRead(2);
  if(buttonRead==HIGH){
  digitalWrite(13,HIGH);}
  else{
    digitalWrite(13,LOW);
  }}
