#include <DHT.h>
#include <SoftwareSerial.h>

// Pin definitions
#define FIRE_PIN 2
#define IR_PIN 3
#define DHT_PIN 4
#define LPG_PIN 5
#define MOTION_PIN 6
#define TRIG_PIN 7
#define ECHO_PIN 8
#define TILT_PIN 9
#define VIBRATION_PIN 10
#define LDR_PIN A1

#define DHT_TYPE DHT11
#define VIBRATION_THRESHOLD 100  // Adjusted threshold for digital reading

DHT dht(DHT_PIN, DHT_TYPE);

// SoftwareSerial RX, TX
SoftwareSerial espSerial(12, 13); // RX, TX

float temperature = 0.0;
long duration;
int distanceCm, distancePer;
String vibrationStatus;

// For vibration detection
unsigned long lastVibrationTime = 0;
const unsigned long vibrationDuration = 1000; // Duration to consider vibration active (ms)

void setup() {
  Serial.begin(9600); // Serial communication with the computer
  espSerial.begin(9600); // Serial communication with the ESP32
  dht.begin();

  pinMode(FIRE_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LPG_PIN, INPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TILT_PIN, INPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  // Read all sensors first
  bool fireDetected = digitalRead(FIRE_PIN) == LOW;
  bool irSensorTriggered = digitalRead(IR_PIN) == HIGH;
  bool motionDetected = digitalRead(MOTION_PIN) == HIGH;
  bool lpgLeakDetected = digitalRead(LPG_PIN) == LOW;
  bool tiltDetected = digitalRead(TILT_PIN) == LOW;
  int lightLevel = analogRead(LDR_PIN);

  // Read temperature
  temperature = dht.readTemperature();

  // Read water level using ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distanceCm = duration * 0.034 / 2;
  distancePer = constrain(map(distanceCm, 10, 0, 0, 100), 0, 100);

  // Improved vibration detection
  if (digitalRead(VIBRATION_PIN) == HIGH) {
    lastVibrationTime = millis();
    vibrationStatus = "Vibration_Detected";
  } else if (millis() - lastVibrationTime < vibrationDuration) {
    // Keep vibration detected status for a short duration
    vibrationStatus = "Vibration_Detected";
  } else {
    vibrationStatus = "No_Vibration";
  }

  // Process other sensor readings into status strings
  String fireStatus = fireDetected ? "Fire_Detected" : "No_Fire";
  String irSensorStatus = irSensorTriggered ? "The door is opened" : "The door is closed";
  String motionStatus = motionDetected ? "Motion_Detected" : "No_Motion";
  String lpgStatus = lpgLeakDetected ? "LPG_Leak_Detected" : "LPG_No_Leakage";
  String tiltStatus = tiltDetected ? "Tilt_Detected" : "No_Tilt";
  String waterLevel = String(distancePer);
  String lightStatus = String(map(lightLevel, 0, 1023, 0, 100));

  // Prepare data to send to ESP32
  String dataToSend = "Fire:" + fireStatus + ",IR:" + irSensorStatus + ",Motion:" + motionStatus +
                      ",Temp:" + String(temperature) + ",LPG:" + lpgStatus + ",Tilt:" + tiltStatus +
                      ",Vibration:" + vibrationStatus + ",Water:" + waterLevel + ",Light:" + lightStatus;

  // Send data to ESP32
  espSerial.println(dataToSend);

  // Print to Serial Monitor (consolidated output)
  Serial.println("Sensor Readings:");
  Serial.println("---------------");
  Serial.println("Fire Status: " + fireStatus);
  Serial.println("Door Status: " + irSensorStatus);
  Serial.println("Motion Status: " + motionStatus);
  Serial.println("Temperature: " + String(temperature) + "°C");
  Serial.println("LPG Status: " + lpgStatus);
  Serial.println("Tilt Status: " + tiltStatus);
  Serial.println("Vibration Status: " + vibrationStatus);
  Serial.println("Water Level: " + waterLevel + "%");
  Serial.println("Light Level: " + lightStatus + "%");
  Serial.println("---------------");
  Serial.println();

  delay(1000); // Faster sampling for better vibration detection
}
