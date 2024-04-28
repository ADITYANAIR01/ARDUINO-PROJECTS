
#define VIBRATION_SENSOR_PIN A0  
#define BUZZER_PIN 3            

// Define threshold for vibration intensity
const int VIBRATION_THRESHOLD = 100;

void setup() {
  pinMode(VIBRATION_SENSOR_PIN, INPUT);  
  pinMode(BUZZER_PIN, OUTPUT);           
  Serial.begin(9600);                    
}

void loop() {
  int sensorValue = analogRead(VIBRATION_SENSOR_PIN);

  Serial.println(sensorValue);

  if (sensorValue > VIBRATION_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(100);  
}
