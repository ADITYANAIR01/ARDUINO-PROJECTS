// CODE IS FOR ARDUINO ONLY AND DOES NOT HAVE CONNECTION TO ESP8266 VUA SERIAL COMMUNICATIONS.
// ALL THE THINS ARE WORKING PERFECTLY EXCEPT DHT 11 NEED OPTIMISATION


#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT11

#define MQ2PIN A0
#define SOILPIN A1
#define IRPIN 2
#define PIRPIN 3
#define TRIGPIN1 4
#define TRIGPIN2 5
#define RELAY1 6
#define RELAY2 7
//#define SERVOPIN 8 // To be used later by RFID
#define BUZZERPIN 9
#define LEDPIN 10

#define WATER_TANK_MAX_LEVEL 20 // in cm
#define WATER_TANK_WARNING_LEVEL 17 // in cm

DHT dht(DHTPIN, DHTTYPE);

int previousTemp = 0;
int previousGas = 0;
int previousSoil = 0;
int previousMotion = LOW; // Initial state of PIR sensor
int previousIR = HIGH;    // Initial state of IR sensor

void setup() {
  Serial.begin(9600);
  pinMode(PIRPIN, INPUT);
  pinMode(IRPIN, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(TRIGPIN2, OUTPUT);

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
  if (abs(gas - previousGas) >= 200) { // Adjust threshold for significant change
    if (gas > previousGas) {
      Serial.println("Gas level increasing! Warning!");
      digitalWrite(BUZZERPIN, HIGH);
      delay(5000);
      digitalWrite(BUZZERPIN, LOW);
    }
    previousGas = gas;
    // Store gas value for later use
  }

  // Read Soil Moisture sensor
  int soil = analogRead(SOILPIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soil);
  if (abs(soil - previousSoil) >= 60) { // Adjust threshold for significant change
    if (soil < 1000) {
      Serial.println("Soil is wet! Turning off water pump.");
      digitalWrite(RELAY1, LOW); // Turn off water pump
    } else {
      Serial.println("Soil is dry! Starting water pump.");
      digitalWrite(RELAY1, HIGH); // Turn on water pump
    }
    previousSoil = soil;
    // Store soil moisture value for later use
  }

  // Read PIR sensor
  int motion = digitalRead(PIRPIN);
  Serial.print("Motion Detected: ");
  Serial.println(motion);
  if (motion != previousMotion) {
    if (motion == HIGH) {
      Serial.println("Motion Detected!");
      digitalWrite(LEDPIN, HIGH); // Turn on LED
      delay(5000); // Keep LED on for 5 seconds
      digitalWrite(LEDPIN, LOW); // Turn off LED
    }
    previousMotion = motion;
    // Store motion value for later use
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
    // Store door status value for later use
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
    // Store water level for later use
  }

  delay(2000); // Adjust as needed for sensor reading frequency
}
