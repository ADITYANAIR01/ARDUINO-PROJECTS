const int ledPin = 9;  // pin ledPin
const int fireSensorPin = 8; // pin Fire sensor

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  // Changed from buzzerPin to ledPin
  pinMode(fireSensorPin, INPUT);
}

void loop()
{
  int fireValue = digitalRead(fireSensorPin);
  Serial.println(fireValue);
  
  if(fireValue == 0)
  {
    digitalWrite(ledPin, HIGH);  // Changed from buzzerPin to ledPin
    delay(200);
  }
  else
  {
    digitalWrite(ledPin, LOW);  // Changed from buzzerPin to ledPin
  }
  
  delay(500);
}
