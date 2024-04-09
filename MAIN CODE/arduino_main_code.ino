#define PIN 9
#define TYPE DHT11
#define RX 13 // Connect ESP's TX PIN to Arduino's Pin No. 12
#define TX 12 // Don't Connect

#include<DHT.h>
#include<SoftwareSerial.h>
SoftwareSerial esp(RX, TX);
DHT dht(PIN, TYPE);

// Pin Connection
const int soilPin = A0;
int soilPer = 0;    //blackb
const int trigPin = 4;
const int echoPin = 5;
const int firePin = 6;
const int motionPin = 7;  // pir 
const int relayPin = 8;
const int lpgPin = 11;
const int irPin = 10; // IR sensor pin
int irStatus = 0; // To store IR sensor status

String waterLevel, fireStatus, motionStatus, soilStatus, lpgStatus, irSensorStatus;
float temperature = 0.0;
long duration;
int distanceCm;
int distancePer = 0;

void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  dht.begin();
  pinMode(soilPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(motionPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lpgPin, INPUT);
  pinMode(irPin, INPUT); 
}

void loop() {
  // Read Distance/Water Level
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distancePer = map(distanceCm, 10, 0, 0, 100);
  if (distancePer > 100) {
    distancePer = 100;
  } else if (distancePer < 0) {
    distancePer = 0;
  }
  waterLevel = (String)distancePer;

  // Fire Status
  if (digitalRead(firePin) == HIGH) {
    fireStatus = "NO fIRE";
  } else {
    fireStatus = "FIRE DETECTED ";
  }

  // Motion Status
  if (digitalRead(motionPin) == HIGH) {
    motionStatus = "Motion_Detected";
  } else {
    motionStatus = "No_Motion";
  }

  // IR Sensor Status
  irStatus = digitalRead(irPin);
  if (irStatus == LOW) {
    irSensorStatus = "Door is closed";
  } else {
    irSensorStatus = "Door is opened";
  }

  // Temperature
  temperature = dht.readTemperature();

  // Soil Moisture
  soilPer = map(analogRead(soilPin), 1023, 0, 0, 100);

  // Relay Control
  if (soilPer > 50) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

  // LPG
  if (digitalRead(lpgPin) == LOW) {
    lpgStatus = "LPG_Leak_Detected";
  } else {
    lpgStatus = "LPG_No_Leakage";
  }

  // Printing All Values
  Serial.println("");
  Serial.println("Water Level: " + waterLevel);
  Serial.println("Motion Status: " + motionStatus);
  Serial.println("Temperature: " + (String)temperature);
  Serial.println("Soil Moisture: " + (String)soilPer);
  Serial.println("Fire Status: " + fireStatus);
  Serial.println("LPG Status: " + lpgStatus);
  Serial.println("IR Sensor Status: " + irSensorStatus);
  Serial.println("");
  delay(5000);

  // Serial Communication
  String URL = "http://www.techvegan.in/firebase.php?";
  esp.print(URL);
  esp.print("water=" + waterLevel + "%");
  esp.print("&motion=" + motionStatus);
  esp.print("&temperature=" + (String)temperature);
  esp.print("&soil=" + (String)soilPer + "%");
  esp.print("&fire=" + fireStatus);
  esp.print("&lpg=" + lpgStatus);
  esp.print("&ir=" + irSensorStatus);
  delay(2000);
}
