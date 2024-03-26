// THIS CODE IS MENT FOR ESP8266 NOCE MCU 
// NODE MCU DOES'T HAVE D9,D10 PINS 

#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Servo.h>

// Define sensor pins and types
const int DHT_PIN = D1;
const int DHT_TYPE = DHT11;
DHT dht(DHT_PIN, DHT_TYPE);

const int GAS_SENSOR_PIN = A0;
const int RELAY_1_PIN = D2;  // Relay pin for controlling soil moisture
const int RELAY_2_PIN = D3;  // Relay pin for other purposes
const int ECHO_PIN = D4;     // Change to a valid pin (D4) for ESP8266
const int SOIL_MOISTURE_PIN = D5;
const int IR_SENSOR_PIN = D6;
const int PIR_SENSOR_PIN = D7;
const int LED_PIN = D8;      // PIR sensor activity indicator
const int SERVO_PIN = D9;
const int TRIGGER_PIN = D10;

// Initialize servo motor
Servo servo;

// Variable to store temperature
float temperature = 0.0;

// Timing variables for gate control
unsigned long gateOpenTime = 0;
const unsigned long gateOpenDuration = 10000; // 10 seconds
const int gateOpenDistance = 10; // Open gate when distance is less than 10 cm
const int gateCloseDistance = 50; // Close gate when distance exceeds 50 cm

// Servo positions
const int servoOpenPosition = 0;
const int servoClosePosition = 190;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin("THE NAIR'S", "adityanair52004");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // Initialize DHT sensor
  dht.begin();

  // Set pin modes
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Attach servo
  servo.attach(SERVO_PIN);

  Serial.println("Setup completed.");
}

void loop() {
  // Read temperature from DHT sensor
  temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);

  // Check DHT sensor reading validity
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Control soil moisture
  controlSoilMoisture();

  // Check door status
  checkDoorStatus();

  // Detect gas leakage
  detectGasLeakage();

  // Detect motion and indicate with LED
  detectMotion();

  // Measure distance using ultrasonic sensor
  measureDistance();

  delay(1000); // Adjust delay as needed
}

// Function to control soil moisture
void controlSoilMoisture() {
  int soilMoisture = digitalRead(SOIL_MOISTURE_PIN);
  digitalWrite(RELAY_1_PIN, soilMoisture == HIGH ? LOW : HIGH);
}

// Function to check door status
void checkDoorStatus() {
  int doorStatus = digitalRead(IR_SENSOR_PIN);
  if (doorStatus == HIGH) {
    Serial.println("Door is opened!");
  }
}

// Function to detect gas leakage
void detectGasLeakage() {
  int gasReading = analogRead(GAS_SENSOR_PIN);
  Serial.print("Gas Sensor Reading: ");
  Serial.println(gasReading);
  if (gasReading > 200) {
    Serial.println("WARNING: Gas leakage detected in your house!");
  }
}

// Function to detect motion and indicate with LED
void detectMotion() {
  int motionDetected = digitalRead(PIR_SENSOR_PIN);
  digitalWrite(LED_PIN, motionDetected);
}

// Function to measure distance using ultrasonic sensor
void measureDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;

  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Open gate if distance is less than gateOpenDistance and gate is not already open
  if (distance < gateOpenDistance && millis() - gateOpenTime >= gateOpenDuration) {
    servo.write(servoOpenPosition); // Open gate (clockwise)
    delay(1000); // Delay for servo to reach position
    gateOpenTime = millis(); // Record the time when gate is opened
    Serial.println("Gate opened");
  }

  // Close gate if distance exceeds gateCloseDistance
  if (distance > gateCloseDistance) {
    servo.write(servoClosePosition); // Close gate (anticlockwise)
    delay(1000); // Delay for servo to reach position
    Serial.println("Gate closed");
  }
}
