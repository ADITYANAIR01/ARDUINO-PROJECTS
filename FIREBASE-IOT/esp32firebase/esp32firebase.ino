#include <WiFi.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>

#define RXD2 16
#define TXD2 17

const char* ssid = "NOTHING";
const char* password = "123456789";

#define API_KEY "AIzaSyAyzdrFz-dMg3MZNu1ti9jWh-WSveRgIgw"
#define DATABASE_URL "https://iot-sensor-app-4dee7-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define SENSOR_DATA_PATH "sensor_data" // Firebase RTDB path

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectFirebase() {
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  bool signupOK = Firebase.signUp(&config, &auth, "", "");
  if (!signupOK) {
    Serial.printf("Firebase signup failed: %s\n", config.signer.signupError.message.c_str());
  }
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void uploadToFirebase(FirebaseJson &json) {
  if (Firebase.RTDB.setJSON(&fbdo, SENSOR_DATA_PATH, &json)) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.printf("Firebase upload failed: %s\n", fbdo.errorReason().c_str());
  }
}

void processData(String data) {
  StaticJsonDocument<400> doc;
  FirebaseJson json;
  String values[9] = {"", "", "", "", "", "", "", "", ""};
  int valueIndex = 0;
  for (size_t i = 0; i < data.length(); i++) {
    char c = data.charAt(i);
    if (c == ',') {
      if (valueIndex < 8) valueIndex++;
      else values[8] += c;
    } else {
      values[valueIndex] += c;
    }
  }
  doc["water_level"] = values[0];
  doc["motion"] = values[1];
  doc["temperature"] = values[2];
  doc["fire"] = values[3];
  doc["lpg"] = values[4];
  doc["ir_sensor"] = values[5];
  doc["tilt"] = values[6];
  doc["vibration"] = values[7];
  doc["light"] = values[8];
  String jsonStr;
  serializeJson(doc, jsonStr);
  json.setJsonData(jsonStr);
  Serial.println("JSON Message:");
  Serial.println(jsonStr);
  uploadToFirebase(json);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  connectWiFi();
  connectFirebase();
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();
    if (data.length() > 0) {
      Serial.println("Received from Arduino: " + data);
      processData(data);
    }
  }
}
