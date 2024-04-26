        // ISSUES TO BE SOLVED 
// gas and temp sensor not printing the output
// gas sensor not givng readings at all 
// GAS SENSOR AND MQ SENSOR ARE THE SAME 

#include <Adafruit_Sensor.h>

// needed libraries
#include <Servo.h>
#include <DHT.h>

// pins and types
const int DHT_PIN = 2;
const int DHT_TYPE = DHT11;
DHT dht(DHT_PIN, DHT_TYPE);

const int MQ_PIN = A0;      // GAS SENSOR
const int RELAY_1_PIN = 3;  // SOIL MOISTURE SENSOR RELAY
const int RELAY_2_PIN = 4;  // Unused
const int SOIL_MOISTURE_PIN = 5; // soil moisture sensor 
const int IR_SENSOR_PIN = 6;  //  IR SENSOR
const int GAS_SENSOR_PIN = A1;  // 
const int PIR_SENSOR_PIN = 8;
const int LED_PIN = 9;      // PIR sensor activity indicator
const int SERVO_PIN = 10;
const int TRIGGER_PIN = 11;
const int ECHO_PIN = 12;

// Initialize servo motor
Servo servo;

// Variable to store temperature
float temperature = 0.0;

// Timing variables for gate control
unsigned long gateOpenTime = 0;
const unsigned long gateOpenDuration = 10000; 
const int gateOpenDistance = 10; // gate will open when distance is less than 10 cm
const int gateCloseDistance = 50; // Close gate when distance exceeds 50 cm

// Servo positions
const int servoOpenPosition = 0;
const int servoClosePosition = 190; // 190 rotation

// Setup function
void setup() {
  Serial.begin(9600);

  // Set pin modes
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Attach servo
  servo.attach(SERVO_PIN);

  // Initialize DHT sensor
  dht.begin();

  // Calibrate PIR sensor 
  calibratePIR();
}

// Loop function
void loop() {
  // Read temperature from DHT sensor
  temperature = dht.readTemperature();

  // Check DHT sensor is available or not  
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // soil moisture
  controlSoilMoisture();

  // door status
  checkDoorStatus();

  // gas leakage
  detectGasLeakage();

  // Detect motion and indicate with LED
  detectMotion();

  // Measure distance using ultrasonic sensor
  measureDistance();
}

// Function to calibrate PIR sensor(important for accurate reading  )
void calibratePIR() {
  Serial.println("Calibrating PIR sensor for 10 seconds...");
  delay(10000);
  Serial.println("PIR sensor calibration done.");
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
  if (gasReading > 300) {
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

  // Close gate if distance exceeds Distance
  if (distance > gateCloseDistance) {
    servo.write(servoClosePosition); // Close gate (anticlockwise)
    delay(1000); // reseting position of servo i.e closing gate
    Serial.println("Gate closed");
  }
}

// THIS CODE IS MENT TO RUN ON ARDUINO UNO R3 

// MADE BY Aditya Nair