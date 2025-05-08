#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Firebase helpers
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Network credentials
#define WIFI_SSID ""     // Your WiFi SSID
#define WIFI_PASSWORD "" // Your WiFi password

// Firebase credentials
#define API_KEY ""          // Your Firebase API key
#define DATABASE_URL ""     // Your Firebase Realtime Database URL

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Serial2 pins for Arduino communication
#define RXD2 16
#define TXD2 17

bool firebaseReady = false;

void setup() {
  Serial.begin(9600);  // For ESP32 Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // For Arduino communication

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to Wi-Fi");

  // Configure Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  // Anonymous signup
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase signup successful");
    firebaseReady = true;
  } else {
    Serial.printf("Firebase signup failed: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void uploadToFirebase(String data) {
  if (!firebaseReady) return;

  // Remove trailing newline or spaces
  data.trim();

  // Parse the string into 9 values
  String values[9];
  int index = 0;
  int commaIndex;
  while ((commaIndex = data.indexOf(',')) != -1 && index < 9) {
    values[index] = data.substring(0, commaIndex);
    data = data.substring(commaIndex + 1);
    index++;
  }
  if (index == 8 && data.length() > 0) {
    values[8] = data; // Last value
  } else {
    Serial.println("Invalid data format - Expected 9 values. Received: " + String(index + 1));
    Serial.println("Raw data: " + data);
    return;
  }

  // Debugging: Print received values
  Serial.println("--- Received Sensor Data ---");
  Serial.println("Water Level: " + values[0]);
  Serial.println("Motion: " + values[1]);
  Serial.println("Temperature: " + values[2]);
  Serial.println("Fire: " + values[3]);
  Serial.println("LPG: " + values[4]);
  Serial.println("IR Sensor: " + values[5]);
  Serial.println("Tilt: " + values[6]);
  Serial.println("Vibration: " + values[7]);
  Serial.println("Light: " + values[8]);
  Serial.println("----------------------------");

  // Upload to Firebase
  Firebase.RTDB.setInt(&fbdo, "sensors/water_level", values[0].toInt());
  Firebase.RTDB.setString(&fbdo, "sensors/motion", values[1]);
  Firebase.RTDB.setFloat(&fbdo, "sensors/temperature", values[2].toFloat());
  Firebase.RTDB.setString(&fbdo, "sensors/fire", values[3]);
  Firebase.RTDB.setString(&fbdo, "sensors/lpg", values[4]);
  Firebase.RTDB.setString(&fbdo, "sensors/ir_sensor", values[5]);
  Firebase.RTDB.setString(&fbdo, "sensors/tilt", values[6]);
  Firebase.RTDB.setString(&fbdo, "sensors/vibration", values[7]);
  Firebase.RTDB.setInt(&fbdo, "sensors/light", values[8].toInt());
  Firebase.RTDB.setInt(&fbdo, "sensors/timestamp", millis() / 1000);

  if (fbdo.httpCode() == 200) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.printf("Upload failed: %s\n", fbdo.errorReason().c_str());
  }
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    if (data.length() > 0) {
      Serial.println("Raw data received: " + data);
      uploadToFirebase(data);
    }
  }
  delay(100); // Small delay to avoid overwhelming the loop
}