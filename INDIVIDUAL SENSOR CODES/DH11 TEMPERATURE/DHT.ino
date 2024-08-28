#include <DHT.h> //LIBRARY
#define DHTPIN 2     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();  //begin the sensor data collection
}

void loop() {
  delay(2000);

  float temp = dht.readTemperature();

  if (isnan(temp)) {  // ERROR HANDLING
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
Serial.print(temp);
Serial.println("  * Celsius ");
}
