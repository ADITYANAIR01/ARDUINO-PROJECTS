const int MQ_PIN = A0;  //pin A0

void setup() {
  // Set the pin mode to INPUT
  pinMode(MQ_PIN, INPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the MQ sensor
  int mqSensorValue = analogRead(MQ_PIN);
  
  // Print the sensor value to the serial monitor
  Serial.println(mqSensorValue);
  
  // Delay for 500 milliseconds
  delay(500);
}
