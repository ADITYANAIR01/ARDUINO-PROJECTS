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
#define VIBRATION_THRESHOLD 500 // Adjust as needed

DHT dht(DHT_PIN, DHT_TYPE);
SoftwareSerial espSerial(RX_PIN, TX_PIN); // RX, TX

float temperature = 0.0;
long duration;
int distanceCm, distancePer;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Communication with ESP32
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
  // Read Water Level
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distanceCm = duration * 0.034 / 2;
  distancePer = map(distanceCm, 10, 0, 0, 100);
  distancePer = constrain(distancePer, 0, 100);
  String waterLevel = String(distancePer);

  // Read Other Sensors
  String fireStatus = (digitalRead(FIRE_PIN) == LOW) ? "No_Fire" : "Fire_Detected";
  String motionStatus = (digitalRead(MOTION_PIN) == HIGH) ? "Motion_Detected" : "No_Motion";
  String irSensorStatus = (digitalRead(IR_PIN) == LOW) ? "Door_is_Closed" : "Door_is_Opened";
  temperature = dht.readTemperature();
  String lpgStatus = (digitalRead(LPG_PIN) == LOW) ? "LPG_Leak_Detected" : "LPG_No_Leakage";
  String tiltStatus = (digitalRead(TILT_PIN) == LOW) ? "Tilt_Detected" : "No_Tilt";
  int vibrationValue = digitalRead(VIBRATION_PIN);
  String vibrationStatus = (vibrationValue > VIBRATION_THRESHOLD) ? "Vibration_Detected" : "No_Vibration";
  int lightValue = analogRead(LDR_PIN);
  String lightStatus = String(map(lightValue, 0, 1023, 0, 100));

  // Send data to ESP32 as CSV format
  String data = waterLevel + "," + fireStatus + "," + motionStatus + "," + 
                irSensorStatus + "," + String(temperature) + "," + lpgStatus + "," + 
                tiltStatus + "," + vibrationStatus + "," + lightStatus;
  espSerial.println(data);

  // Print to Serial Monitor
  Serial.println("Water Level: " + waterLevel + "%");
  Serial.println("Fire Status: " + fireStatus);
  Serial.println("Motion Status: " + motionStatus);
  Serial.println("IR Sensor: " + irSensorStatus);
  Serial.println("Temperature: " + String(temperature));
  Serial.println("LPG Status: " + lpgStatus);
  Serial.println("Tilt Status: " + tiltStatus);
  Serial.println("Vibration Status: " + vibrationStatus);
  Serial.println("Light Level: " + lightStatus + "%");
  Serial.println("");

  delay(5000); // Delay for stability
}
