#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

const char* ssid = "NAIR'S";
const char* password = "adityanair52004";
const char* phpScriptUrl = "http://techvegan.in/firebase.php"; // Replace with your PHP script URL

#define DHTPIN 2 // Pin D4 corresponds to GPIO2 on ESP8266
#define DHTTYPE DHT11

#define MQ2PIN 34
#define SOILPIN 34 // Connect the soil moisture sensor to analog pin A0
#define IRPIN 27 // GPIO5
#define PIRPIN 4 // GPIO4
#define TRIGPIN1 33 // GPIO0
#define TRIGPIN2 14 // GPIO14
#define RELAYPIN 12 // GPIO12, replaced 2-channel relay with 1-channel
#define BUZZERPIN 15 // GPIO15
#define LEDPIN 16 // GPIO16
#define FIRE_SENSOR_PIN 26 // GPIO26, added fire sensor

#define WATER_TANK_MAX_LEVEL 20 // in cm
#define WATER_TANK_WARNING_LEVEL 17 // in cm

DHT dht(DHTPIN, DHTTYPE);

int previousTemp = 0;
int previousGas = 0;
int previousSoil = 0;
int previousMotion = LOW; // Initial state of PIR sensor
int previousIR = HIGH;    // Initial state of IR sensor
int previousFireStatus = LOW; // Initial state of fire sensor

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi");
    delay(2000);
  }

  Serial.println("Connected");

  pinMode(PIRPIN, INPUT);
  pinMode(IRPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(TRIGPIN2, OUTPUT);
  pinMode(FIRE_SENSOR_PIN, INPUT); // Set fire sensor as input

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

  if (temp > 30) {
    Serial.println("Temperature is above 30°C! Activating buzzer.");
    digitalWrite(BUZZERPIN, HIGH);
    delay(3000);
    digitalWrite(BUZZERPIN, LOW);
  }

  // Read MQ2 sensor
  int gas = analogRead(MQ2PIN);
  Serial.print("Gas Level: ");
  Serial.println(gas);
  if (abs(gas - previousGas) >= 200) {
    if (gas > previousGas) {
      Serial.println("Gas level increasing! Warning!");
      digitalWrite(BUZZERPIN, HIGH);
      delay(5000);
      digitalWrite(BUZZERPIN, LOW);
    }
    previousGas = gas;
  }

  // Read Soil Moisture sensor
  int soil = analogRead(SOILPIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soil);
  if (abs(soil - previousSoil) >= 60) {
    if (soil < 1000) {
      Serial.println("Soil is wet! Turning off water pump.");
      digitalWrite(RELAYPIN, LOW);
    } else {
      Serial.println("Soil is dry! Starting water pump.");
      digitalWrite(RELAYPIN, HIGH);
    }
    previousSoil = soil;
  }

  // Read PIR sensor
  int motion = digitalRead(PIRPIN);
  Serial.print("Motion Detected: ");
  Serial.println(motion);
  if (motion != previousMotion) {
    if (motion == HIGH) {
      Serial.println("Motion Detected!");
      digitalWrite(LEDPIN, HIGH);
      delay(5000);
      digitalWrite(LEDPIN, LOW);
    }
    previousMotion = motion;
  }

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

  // Read Fire sensor
  int fireStatus = digitalRead(FIRE_SENSOR_PIN);
  if (fireStatus != previousFireStatus) {
    if (fireStatus == HIGH) {
      Serial.println("Fire Detected!");
    } else {
      Serial.println("Fire not detected.");
    }
    previousFireStatus = fireStatus;
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

  // Sample sensor data, replace with actual sensor readings
  String lpg = String(gas);
  String ir = String(previousIR);
  String fire_status = String(fireStatus); // Update fire status
  String waterStatus = String(soil < 1000 ? 0 : 1); // Assuming soil moisture below 1000 indicates dry soil
  String temperature = String(temp);

  // Send sensor data to PHP script
  sendDataToPHP(lpg, ir, fire_status, waterStatus, temperature);

  delay(20000); // Adjust delay according to your requirements
}

void sendDataToPHP(String lpg, String ir, String fire_status, String waterStatus, String temperature) {
  // Construct URL with sensor data
  String url = phpScriptUrl;
  url += "?lpg=" + lpg;
  url += "&ir=" + ir;
  url += "&fire_status=" + fire_status; // Add fire status to URL
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
