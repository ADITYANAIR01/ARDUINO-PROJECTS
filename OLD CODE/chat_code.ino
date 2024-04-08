#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

const char* ssid = "NAIR'S";
const char* password = "adityanair52004";
const char* phpScriptUrl = "http://techvegan.in/firebase.php"; // Replace with your PHP script URL

#define DHTPIN 2 // Pin D4 corresponds to GPIO2 on ESP8266
#define DHTTYPE DHT11

#define MQ2PIN 34
#define FIREPIN 26 // Connect the fire sensor to GPIO35
#define SOILPIN 34 // Connect the soil moisture sensor to analog pin A0
#define IRPIN 27 // GPIO27
#define PIRPIN 4 // GPIO4
#define TRIGPIN1 33 // GPIO0
#define TRIGPIN2 14 // GPIO14
#define RELAY1 12 // GPIO12 (1-channel relay)
#define BUZZERPIN 15 // GPIO15
#define LEDPIN 16 // GPIO16
#define BUTTONPIN 13 // GPIO13 for the button

#define WATER_TANK_MAX_LEVEL 20 // in cm
#define WATER_TANK_WARNING_LEVEL 17 // in cm

DHT dht(DHTPIN, DHTTYPE);

int previousTemp = 0;
int previousGas = 0;
int previousSoil = 0;
int previousMotion = LOW; // Initial state of PIR sensor
int previousIR = HIGH;    // Initial state of IR sensor
int previousFire = LOW;   // Initial state of fire sensor

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  pinMode(BUTTONPIN, INPUT_PULLUP); // Button as an input with internal pull-up resistor

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi");
    delay(2000);
  }

  Serial.println("Connected");
  
  pinMode(PIRPIN, INPUT);
  pinMode(IRPIN, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(TRIGPIN2, OUTPUT);
  pinMode(FIREPIN, INPUT); // Fire sensor pin

  // Calibrating PIR sensor
  Serial.println("Calibrating PIR sensor...");
  delay(20000); // Calibrate for 20 seconds
  Serial.println("PIR sensor calibrated.");
}

void loop() {
  // Read DHT11 sensor
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C");

  // Read MQ2 sensor
  int gas = analogRead(MQ2PIN);
  Serial.print("Gas Level: ");
  Serial.println(gas);

  // Read Fire sensor
  int fire = digitalRead(FIREPIN);
  Serial.print("Fire Detected: ");
  Serial.println(fire);

  // Read Soil Moisture sensor
  int soil = analogRead(SOILPIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soil);

  // Read PIR sensor
  int motion = digitalRead(PIRPIN);
  Serial.print("Motion Detected: ");
  Serial.println(motion);

  // Read IR sensor
  int door = digitalRead(IRPIN);
  if (door != previousIR) {
    if (door == HIGH) {
      Serial.println("Door is opened.");
    } else {
      Serial.println("Door is closed.");
    }
    previousIR = door;
  }

  // Read Ultrasonic sensor
  long duration1, duration2, distance;
  digitalWrite(TRIGPIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);
  duration1 = pulseIn(TRIGPIN1, HIGH);

  digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN2, LOW);
  duration2 = pulseIn(TRIGPIN2, HIGH);

  distance = duration1 * 0.034 / 2;
  if (distance != 0 && distance <= WATER_TANK_MAX_LEVEL) {
    Serial.print("Water level: ");
    Serial.print(distance);
    Serial.println("cm");

    if (distance >= WATER_TANK_WARNING_LEVEL && distance <= 17) {
      Serial.println("Warning: Water tank almost full!");
    } else if (distance > WATER_TANK_WARNING_LEVEL) {
      Serial.println("Water tank full! Overflowing!");
    }
  }
  
  // Send sensor data to PHP script
  String lpg = String(gas);
  String ir = String(previousIR);
  String fireStatus = String(fire); 
  String waterStatus = String(soil < 1000 ? 0 : 1); 
  String temperature = String(temp);
  
  sendDataToPHP(lpg, ir, fireStatus, waterStatus, temperature);

  // Check button press
  if (digitalRead(BUTTONPIN) == LOW) {
    Serial.println("CONTACT EMERGENCY SERVICES (112)");
    delay(1000); // Debounce delay
  }

  delay(20000); // Adjust delay according to your requirements
}

void sendDataToPHP(String lpg, String ir, String fireStatus, String waterStatus, String temperature) {
  // Construct URL with sensor data
  String url = phpScriptUrl;
  url += "?lpg=" + lpg;
  url += "&ir=" + ir;
  url += "&fire_status=" + fireStatus;
  url += "&water_status=" + waterStatus;
  url += "&temperature=" + temperature;
  
  // Send HTTP GET request to PHP script
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println("Server response: " + payload);
  } else {
    Serial.print("Error sending data to server. HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
}
