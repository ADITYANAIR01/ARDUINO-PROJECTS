#include <DHT.h>
#include <SoftwareSerial.h>

// Pin definitions
#define FIRE_PIN 1
#define IR_PIN 2
#define DHT_PIN 3
#define LPG_PIN 4
#define MOTION_PIN 6
#define TRIG_PIN 7
#define ECHO_PIN 8
#define TILT_PIN 9
#define VIBRATION_PIN 10
#define LED_PIN 11
#define LDR_PIN A1

#define RX_PIN 13
#define TX_PIN 12

#define DHT_TYPE DHT11
#define VIBRATION_THRESHOLD 500 // Adjust this value based on your sensor's sensitivity

DHT dht(DHT_PIN, DHT_TYPE);
SoftwareSerial esp(RX_PIN, TX_PIN);

String waterLevel, fireStatus, motionStatus, lpgStatus, irSensorStatus, tiltStatus, vibrationStatus, lightStatus;
float temperature = 0.0;
long duration;
int distanceCm, distancePer;

void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  dht.begin();
  
  pinMode(FIRE_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LPG_PIN, INPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TILT_PIN, INPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  // Read Distance/Water Level
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distanceCm = duration * 0.034 / 2;
  distancePer = map(distanceCm, 10, 0, 0, 100);
  distancePer = constrain(distancePer, 0, 100);
  waterLevel = String(distancePer);

  // Fire Status
  fireStatus = (digitalRead(FIRE_PIN) == LOW ) ? "Fire_Detected" : "No_Fire" ;

  // Motion Status
  motionStatus = (digitalRead(MOTION_PIN) == HIGH) ? "Motion_Detected" : "No_Motion";

  // IR Sensor Status
  irSensorStatus = (digitalRead(IR_PIN) == LOW) ? "Door_is_Closed" : "Door_is_Opened";

  // Temperature
  temperature = dht.readTemperature();

  // LPG
  lpgStatus = (digitalRead(LPG_PIN) == LOW) ? "LPG_Leak_Detected" : "LPG_No_Leakage";

  // Tilt Sensor
  tiltStatus = (digitalRead(TILT_PIN) == HIGH ) ? "Tilt_Detected" : "No_Tilt";

  // Vibration Sensor
   int vibrationValue = digitalRead(VIBRATION_PIN); // Read digital value
  vibrationStatus = (vibrationValue == HIGH) ? "Vibration_Detected" : "No_Vibration";


  // Light Sensor
  int lightValue = analogRead(LDR_PIN);
  lightStatus = String(map(lightValue, 0, 1023, 0, 100));

  // Print all values
  Serial.println("");
  Serial.println("Water Level: " + waterLevel + "%");
  Serial.println("Motion Status: " + motionStatus);
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Fire Status: " + fireStatus);
  Serial.println("LPG Status: " + lpgStatus);
  Serial.println("IR Sensor Status: " + irSensorStatus);
  Serial.println("Tilt Status: " + tiltStatus);
  Serial.println("Vibration Status: " + vibrationStatus);
  Serial.println("Light Level: " + lightStatus + "%");
  Serial.println("");

  // Send data to ESP32
  String data = waterLevel + "," + motionStatus + "," + String(temperature) + "," + 
                fireStatus + "," + lpgStatus + "," + irSensorStatus + "," + 
                tiltStatus + "," + vibrationStatus + "," + lightStatus;
  esp.println(data);

  delay(5000);
}