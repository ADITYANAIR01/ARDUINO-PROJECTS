// Define pin assignments
#define LDR_PIN A0   // LDR connected to analog pin A0
#define LED_PIN 2    // LED connected to digital pin 2

void setup() {
  pinMode(LDR_PIN, INPUT);   // Set LDR pin as input
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
  
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int ldr_readings = analogRead(LDR_PIN);
  
  Serial.println(ldr_readings);
  
  if (ldr_readings <= 100) {
    digitalWrite(LED_PIN, LOW);  
    Serial.println("there is  light :) ");
  } else {
    digitalWrite(LED_PIN, HIGH);   
    Serial.println("there is no light :( ");
  }

  delay(1000);  
}
