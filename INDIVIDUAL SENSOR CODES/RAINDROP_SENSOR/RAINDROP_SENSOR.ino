#define RAIN 34  // Using GPIO34, an analog input pin on ESP32 and A3

// Rain threshold constants (adjustable based on your sensor)
const int NO_RAIN_THRESHOLD = 3900;
const int LIGHT_RAIN_THRESHOLD = 3700;
const int MODERATE_RAIN_THRESHOLD = 2800;
// Heavy rain is anything below MODERATE_RAIN_THRESHOLD

// Number of samples to average for smoothing
const int SAMPLE_COUNT = 5;
// Hysteresis to prevent flickering between states (optional)
const int HYSTERESIS = 50;

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
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
  
  if (reading >= NO_RAIN_THRESHOLD) {
    Serial.println("Condition: No rain detected");
  } 
  else if (reading >= LIGHT_RAIN_THRESHOLD - HYSTERESIS) {
    Serial.println("Condition: Light rain detected");
    Serial.println("Alert: It is raining outside!");
    Serial.println("Action: If there are any clothes outside, you better pick them up now!");
  } 
  else if (reading >= MODERATE_RAIN_THRESHOLD - HYSTERESIS) {
    Serial.println("Condition: Moderate rain detected");
  } 
  else {
    Serial.println("Condition: HEAVY RAIN OBSERVED");
    Serial.println("Alert: THERE IS HEAVY RAIN OUTSIDE!");
    Serial.println("Action: IT IS ADVISED TO STAY INSIDE");
  }
  Serial.println("-------------------");
}

void loop() {
  int rain_status = getAveragedReading();  // Get smoothed reading
  printRainStatus(rain_status);  // Print status based on reading
  delay(1000);  // Wait 1 second between full cycles
}