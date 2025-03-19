#define RAIN A3  // Using pin A3 on Arduino Uno

// Rain threshold constants for 10-bit ADC (0-1023 range)
const int RAIN_THRESHOLD = 850;    // Light rain threshold
const int HEAVY_RAIN_THRESHOLD = 500;  // Heavy rain threshold

// Number of samples to average for smoothing
const int SAMPLE_COUNT = 10;

void setup() {
  Serial.begin(9600);  // Initialize serial at 9600 baud
  pinMode(RAIN, INPUT);  // Set rain sensor pin as input
  Serial.println("Rain Sensor Initialized");
}

int getAveragedReading() {
  long total = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(RAIN);
    delay(100);  // Small delay between samples
  }
  return total / SAMPLE_COUNT;  // Return averaged value
}

void printRainStatus(int reading) {
  Serial.print("Rain Sensor Value: ");
  Serial.println(reading);
  
  if (reading >= RAIN_THRESHOLD) {
    Serial.println("Condition: No rain detected");
  } 
  else if (reading >= HEAVY_RAIN_THRESHOLD) {
    Serial.println("Condition: Rain detected");
    Serial.println("Watch out for clothes outside!");
  } 
  else {
    Serial.println("Condition: There is heavy rain");
  }
  Serial.println("-------------------");
}

void loop() {
  int rain_status = getAveragedReading();  // Get smoothed reading
  printRainStatus(rain_status);  // Print status based on reading
  delay(1000);  // Wait 1 second between cycles
}