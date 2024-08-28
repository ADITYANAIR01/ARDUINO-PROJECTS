# define TILT 2 
# define BUZZER 3 
void setup() {
  Serial.begin(9600);
  pinMode(TILT, INPUT);
  pinMode(BUZZER, OUTPUT);

}

void loop() {
  int TILT_VALUE = digitalRead(TILT);
  if(TILT_VALUE == LOW ){
    digitalWrite(BUZZER, HIGH);
    Serial.println("THERE IS TILT ");
    delay (1000);
  }
  else {
    digitalWrite(BUZZER, LOW);
  }

}
