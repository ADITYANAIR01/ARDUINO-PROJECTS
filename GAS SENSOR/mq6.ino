int mq=A0; // PINS TO BE CONNECT
int x;

void setup() 
{
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  x=analogRead(A0);
  Serial.println(x);
  delay(500);
}
