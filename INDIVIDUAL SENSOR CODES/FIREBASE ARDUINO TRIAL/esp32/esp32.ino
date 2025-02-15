#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "time.h"

// Serial communication pins with Arduino
#define RX_PIN 16 // Connect to TX of Arduino
#define TX_PIN 17 // Connect to RX of Arduino

// Wi-Fi Credentials
#define WIFI_SSID "NOTHING"
#define WIFI_PASSWORD "123456789"

// Firebase Credentials
#define API_KEY "AIzaSyAyzdrFz-dMg3MZNu1ti9jWh-WSveRgIgw"
#define DATABASE_URL "https://iot-sensor-app-4dee7-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
HardwareSerial arduinoSerial(1); // Use UART1

bool firebaseReady = false;

void connectWiFi() {
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to Wi-Fi!");
    } else {
        Serial.println("\nFailed to connect. Restarting...");
        ESP.restart();
    }
}

void initFirebase() {
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("Firebase Signup Successful!");
        firebaseReady = true;
    } else {
        Serial.printf("Firebase Signup Failed: %s\n", config.signer.signupError.message.c_str());
    }

    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void setup() {
    Serial.begin(115200);
    arduinoSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
    connectWiFi();
    initFirebase();
}

void loop() {
    if (arduinoSerial.available()) {
        String message = arduinoSerial.readStringUntil('\n');
        message.trim();

        if (message.length() > 0) {
            Serial.println("Received from Arduino: " + message);

            // Parse data from Arduino (CSV format)
            String values[9];
            int index = 0;
            for (int i = 0; i < message.length(); i++) {
                if (message[i] == ',') {
                    index++;
                } else {
                    values[index] += message[i];
                }
            }

            if (Firebase.ready() && firebaseReady) {
                Firebase.RTDB.setString(&fbdo, "/sensor_data/water_level", values[0]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/fire_status", values[1]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/motion_status", values[2]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/ir_status", values[3]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/temperature", values[4]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/lpg_status", values[5]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/tilt_status", values[6]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/vibration_status", values[7]);
                Firebase.RTDB.setString(&fbdo, "/sensor_data/light_level", values[8]);

                Serial.println("Data sent to Firebase successfully");
            }
        }
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi disconnected. Reconnecting...");
        connectWiFi();
    }
}
