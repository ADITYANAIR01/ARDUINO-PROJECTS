
#define LDR_PIN A0   
#define LED_PIN 2    

void setup() {
  pinMode(LDR_PIN, INPUT);   
  pinMode(LED_PIN, OUTPUT);  
  
  Serial.begin(9600);  
}

void loop() {
  int ldr_readings = analogRead(LDR_PIN);
  
  Serial.println(ldr_readings);
  
  if (ldr_readings <= 100) {
    digitalWrite(LED_PIN, LOW);  // LED OFF
    Serial.println("there is  light :) ");
  } else {
    digitalWrite(LED_PIN, HIGH);   // LED ON
    Serial.println("there is no light :( ");
  }

  delay(1000);  
}
