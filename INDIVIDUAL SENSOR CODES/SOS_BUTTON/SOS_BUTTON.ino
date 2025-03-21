# define BUTTON_PIN 2
# define LED_PIN 3

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool value = digitalRead(2);
  if (value == 1) {
    digitalWrite(LED_PIN, LOW);
   //  Serial.println(" THERE IS NO EMERGENCY ");
    
  } else {
    digitalWrite(LED_PIN,HIGH);
    Serial.println(" SOS BUTTON PUSHED ");
    Serial.println("CHANGING TO HOUSE  & MONITORING ");

    delay(10000);
  }
}