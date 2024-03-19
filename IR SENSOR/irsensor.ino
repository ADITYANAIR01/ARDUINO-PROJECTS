int ir=7; // PINS WE HAVE CONNECTED TO 
int buzzer=8;
int x;

void setup() 
{
  Serial.begin(9600);
  pinMode(7,INPUT);
 pinMode(8,OUTPUT);
 
}

void loop() 
{
x=digitalRead(ir);
Serial.println(x);
delay(300);

if(x==1)      //Sensor not activated
{
  digitalWrite(8,LOW);
}

else         //Sensor Activated[when x is 0]
{
  digitalWrite(8,HIGH);
}

}
