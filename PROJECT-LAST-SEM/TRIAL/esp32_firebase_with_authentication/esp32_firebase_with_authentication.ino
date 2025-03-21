#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
// Firebase helpers
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
// Network credentials
#define WIFI_SSID "NOTHING"
#define WIFI_PASSWORD "123456789"
// Firebase credentials
#define API_KEY "AIzaSyBapu1aKdh4VX64t5dgfHxkmHDM6EdKstU"
#define DATABASE_URL "https://iot-sensor-dashboard-2025-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define USER_EMAIL "republicofgamers80085@gmail.com"
#define USER_PASSWORD "rogadityanair69"
// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
// Serial2 pins for Arduino communication
#define RXD2 16
#define TXD2 17
bool firebaseReady = false;
String uid;

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
  Serial.println(WiFi.localIP());
  
  // Configure Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  
  // Email sign-in
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  
  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);
  config.max_token_generation_retry = 5;
  
  // Initialize Firebase
  Firebase.begin(&config, &auth);
  
  // Getting the user UID
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);
  
  if (uid == "XGagirN2xeb0ds7ypEbl0GsjNzs1") {
    Serial.println("User authenticated successfully");
    firebaseReady = true;
  } else {
    Serial.println("User authentication failed - UID mismatch");
  }
}

void uploadToFirebase(String data) {
  if (!firebaseReady) return;
  
  // Check for token expiration
  if (Firebase.isTokenExpired()) {
    Firebase.refreshToken(&config);
    Serial.println("Firebase token refreshed");
  }
  
  // Remove trailing newline or spaces
  data.trim();
  
  // Parse the string into 11 values (added button)
  String values[11];
  int index = 0;
  int commaIndex;
  while ((commaIndex = data.indexOf(',')) != -1 && index < 11) {
    values[index] = data.substring(0, commaIndex);
    data = data.substring(commaIndex + 1);
    index++;
  }
  if (index == 10 && data.length() > 0) {
    values[10] = data; // Last value (button)
  } else {
    Serial.println("Invalid data format - Expected 11 values. Received: " + String(index + 1));
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
  Serial.println("Rain: " + values[9]);
  Serial.println("Button: " + values[10]);  // Added button
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
  Firebase.RTDB.setString(&fbdo, "sensors/rain", values[9]);
  Firebase.RTDB.setString(&fbdo, "sensors/button", values[10]);  // Added button
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