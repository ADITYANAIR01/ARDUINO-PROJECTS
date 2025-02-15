#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "time.h"

// Define serial pins for communication with Arduino
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

// Serial Communication with Arduino
HardwareSerial arduinoSerial(1); // Use UART1

// Timing Variables
unsigned long lastSendTime = 0;
const long sendInterval = 2000; // 2 seconds

bool firebaseReady = false;

void connectWiFi() {
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) { // 15s timeout
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to Wi-Fi!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to Wi-Fi. Restarting...");
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

String getTimestamp() {
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo)) {
        Serial.println("Failed to obtain time");
        return "";
    }

    char timeString[20];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return String(timeString);
}

void setup() {
    Serial.begin(115200);
    arduinoSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

    connectWiFi();
    initFirebase();

    // Configure time synchronization
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    Serial.println("Time synchronization initialized.");
}

void loop() {
    if (arduinoSerial.available()) {
        String message = arduinoSerial.readStringUntil('\n');
        message.trim(); // Remove extra spaces or newlines

        if (message.length() > 0) {
            Serial.println("Received from Arduino: " + message);

            if (Firebase.ready() && firebaseReady) {
                String timestamp = getTimestamp();
                if (timestamp != "") {
                    FirebaseJson json;
                    json.set("value", message);
                    json.set("timestamp", timestamp);

                    if (Firebase.RTDB.setJSON(&fbdo, "sensor_data/data", &json)) {
                        Serial.println("Data sent to Firebase successfully");
                    } else {
                        Serial.println("Failed to send data to Firebase. Reason: " + fbdo.errorReason());
                    }
                }
            }
        }
    }

    // Ensure Wi-Fi stays connected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi disconnected. Reconnecting...");
        connectWiFi();
    }
}
