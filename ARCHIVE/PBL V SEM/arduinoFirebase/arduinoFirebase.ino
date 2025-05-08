#include <DHT.h>
#include <SoftwareSerial.h>

// Pin definitions
#define BUTTON_PIN 2 
#define FIRE_PIN 3
#define IR_PIN 4
#define DHT_PIN 5
#define VIBRATION_PIN 6    
#define MOTION_PIN 7
#define TRIG_PIN 8
#define ECHO_PIN 9
#define TILT_PIN 10
#define LED_PIN 11
#define RX_PIN 13
#define TX_PIN 12
#define LDR_PIN A1
#define LPG_PIN A2
#define RAIN A3  

#define DHT_TYPE DHT11
#define LPG_THRESHOLD 130    
// Rain threshold constants for 10-bit ADC (0-1023 range)

const int RAIN_THRESHOLD = 750;    // Light rain threshold
const int HEAVY_RAIN_THRESHOLD = 500;  // Heavy rain threshold
const int SAMPLE_COUNT = 10;  // Number of samples for rain sensor averaging

DHT dht(DHT_PIN, DHT_TYPE);
SoftwareSerial esp(RX_PIN, TX_PIN);

String waterLevel, fireStatus, motionStatus, lpgStatus, irSensorStatus, tiltStatus, vibrationStatus, lightStatus, rainStatus, buttonStatus;
float temperature = 0.0;
long duration;
int distanceCm, distancePer;

void setup() {
  Serial.begin(9600);  // For Serial Monitor
  esp.begin(9600);     // For ESP32 communication
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
  pinMode(RAIN, INPUT);  // Set rain sensor pin as input
  pinMode(BUTTON_PIN, INPUT);  // Added button pin setup
}

// Function to get averaged rain sensor reading
int getAveragedReading() {
  long total = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(RAIN);
    delay(100);  // Small delay between samples
  }
  return total / SAMPLE_COUNT;  // Return averaged value
}

// Function to determine rain status
void setRainStatus(int reading) {
  if (reading >= RAIN_THRESHOLD) {
    rainStatus = "No_Rain";
  } 
  else if (reading >= HEAVY_RAIN_THRESHOLD) {
    rainStatus = "Light_Rain";
  } 
  else {
    rainStatus = "Heavy_Rain";
  }
}

void loop() {
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
  fireStatus = (digitalRead(FIRE_PIN) == LOW) ? "Fire_Detected" : "No_Fire";

  // Motion Status
  motionStatus = (digitalRead(MOTION_PIN) == HIGH) ? "Motion_Detected" : "No_Motion";

  // IR Sensor Status
  irSensorStatus = (digitalRead(IR_PIN) == LOW) ? "Door_is_Closed" : "Door_is_Opened";

  // Temperature (DHT11)
  temperature = dht.readTemperature();
  if (isnan(temperature)) temperature = 0.0; // Handle invalid readings

  // LPG Status
  int gasValue = analogRead(LPG_PIN);
  lpgStatus = (gasValue <= LPG_THRESHOLD) ? "LPG_Leak_Detected" : "LPG_No_Leakage";

  // Tilt Sensor
  tiltStatus = (digitalRead(TILT_PIN) == LOW) ? "Tilt_Detected" : "No_Tilt";

  // Vibration Sensor 
  vibrationStatus = (digitalRead(VIBRATION_PIN) == HIGH) ? "Vibration_Detected" : "No_Vibration";

  // Light Sensor (LDR)
  int lightValue = analogRead(LDR_PIN);
  lightStatus = String(map(lightValue, 0, 1023, 0, 100));

  // Rain Sensor
  int rainReading = getAveragedReading();
  setRainStatus(rainReading);

  // Button Status
  buttonStatus = (digitalRead(BUTTON_PIN) == HIGH) ? "Button_OFF" : "Button_ON";

  // Print to Arduino Serial Monitor
  Serial.println("--- Sensor Readings ---");
  Serial.println("Water Level: " + waterLevel + "%");
  Serial.println("Motion: " + motionStatus);
  Serial.println("Temperature: " + String(temperature) + "°C");
  Serial.println("Fire: " + fireStatus);
  Serial.println("LPG: " + lpgStatus);
  Serial.println("IR Sensor: " + irSensorStatus);
  Serial.println("Tilt: " + tiltStatus);
  Serial.println("Vibration: " + vibrationStatus);
  Serial.println("Light: " + lightStatus + "%");
  Serial.println("Rain: " + rainStatus);
  Serial.println("Button: " + buttonStatus);  // Added button status print
  Serial.println("-----------------------");

  // Send data to ESP32 (now 11 values including button status)
  String data = waterLevel + "," + motionStatus + "," + String(temperature) + "," + 
                fireStatus + "," + lpgStatus + "," + irSensorStatus + "," + 
                tiltStatus + "," + vibrationStatus + "," + lightStatus + "," + 
                rainStatus + "," + buttonStatus + "\n";
  esp.print(data);

  delay(5000); // Update every 5 seconds
}