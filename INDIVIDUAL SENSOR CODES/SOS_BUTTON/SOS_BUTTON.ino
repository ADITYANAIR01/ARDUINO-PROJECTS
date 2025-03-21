# define BUTTON_PIN 2

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
 int button;
 button = digitalRead(BUTTON_PIN);

 if(button == LOW){
  Serial.println("ON");
 } else {
  Serial.println("OFF");

 }
 delay(1000);
}