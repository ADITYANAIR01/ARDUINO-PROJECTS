MODULE 1 

 1. provide full optimized code with clear comments and a very good logic for the below code and update the code to my requirements mentioned above .   
 
 MODULE 1

* I have these sensors and the pins to be connected to arduino uno 

1. dht11 to pin 3 
2. MQ SENSOR to pin A0
3. soil moisture pin to pin A1
4. IR SENSOR to pin 4
5. pir sensor to pin 5
6. Ultrasonic sensor trig to pin 6 
7. Ultrasonic sensor trig to pin 7
8. relay pin 1 to pin 8 //dual channel relay 
9. relay pin 2 to pin 9 //dual channel relay
10. servo pin to pin 10 
11. D11 and D12 is for serial communication from arduino uno to esp 8266 


The code should be cutomized in such a way 
                                                    
ultrasonic sensors are ment to 1

ir sensor is to be installed in the gate and when the gate opens sensor will sense it and print the message (HOUSE DOOR IS OPENED ) and when the gate close print the message (HOUSE DOOR  IS CLOSED )

if the gas sensors detect the gas concentraion rises print (GAS IS LEAKING )

calibrate pir sensor and let the led glow when there is motion and print motion detected after 10 second recalibrate the pir sensor without printing anything 

print the temperature in the serial monitor 

when the soil is dry print the soil is dry starting the pump via relay 1 when the soil is wet turn off the realy and print the soil is moist and wet 

 HOW TO CONNECT ARDUINO UNO TO ESP 8266 VIA PINS RX AND TX PINS 
 WHAT PINS TO USE FOR THIS I ARDUINO AND ESP8266
 HOW TO UPLOAD CODE ACCORDINGLY 
 THE ALL READING SHOULD BE VISIBLE IN BOTH SERIAL MONITORS arduino and node mcu for now
 HOW TO CORRECLTY FETCH READING FROM ARDUINO UNO TO ESP8266
 SETTING UP FIREBASE FOR SENSOR READING AND REALTIME DATA
7. SETTING UP FIREBASE IN NODE MCU IN SUCH A WAY THAT OT SHOULD UPLOAD THE REALTIME DATA TO FIREBASE 
7. AND HOW TO UPLOAD THE READING TO FIREBASE USING ARDUINO COMMUNICATION VIA SERIAL PINS AND UPLOADING THE REALTIME READINGS TO FIREBASE 

   






                                  MODULE 2 
// wires 

F-F  27 
4 red 
5 yellow
6 white 
4 black 
4 blue 
4 grey


M-F 22
5 YELLOW 
1 BLACK 
2 WHITE
2 BLUE
4 RED
8 grey 


M-M 32
5 YELOW 
4 WHITE
3 BLCK 
6 RED 
5 BLUE 
9 GREY 


ULTRASONIC SENSOR F-F
VCC         WHITE
GND         RED
TRIG        YELLOW
ECHO        BLUE

PIR SENSOR
VCC (RIGHT)  BLACK  
GNC (LEFT)   WHITE
OUT / DATA   YELLOW 

IR SENSOR 
VCC (RIGHT)      GREY 
GND (MIDDLE)     RED 
OUT/DATA (LEFT)  YELLOW 

MQ2 / GAS SENSOR  
VCC (RIGHT)         GREY 
GND (BEFORE VCC)    RED
AO (BEFORE GND)     WHITE
DO (LEFT)

DHT 11 TEMPERATURE SENSOR
VCC (RIGHT)        BLACK
OUT/DATA (MIDDLE)  GREY   
GND (LEFT)        RED

2 CHANNEL RELAY MODULE
GND (LEFT)        WHITE
IN1 (AFTER GND)   BLUE     
IN2(AFTER IN1)    YELLOW
VCC (RIGHT)       BLACK

SERVO MOTOR 
BROWN         GND
RED           VCC
YELLOW        DIGITAL/OUT


SOIL MOISTURE SENSOR  
VCC     WHITE
GND     RED
AO 
DO      YELLOW 



 I have these sensors and the pins to be connected to arduino uno provide me with brief code that is made according to the conditions mentioned below without adding any more sensor or misplacing amy sensor. 

1. dht11 to pin 13 
2. MQ2 SENSOR to pin A0
3. soil moisture pin to pin A1
4. IR SENSOR to pin 2
5. pir sensor to pin 3
6. Ultrasonic sensor trig to pin 4 // i have only 1 pin of this sensor
7. Ultrasonic sensor trig to pin 5 //  i have only 1 pin of this sensor
8. relay pin 1 to pin 6 //dual channel relay 
9. relay pin 2 to pin 7 //dual channel relay
// 10. servo pin to pin 8 TO BE LATER USED BY RFID DO NOT PROVIDE CODE FOR THIS TWO
11. BUZZER PIN TO PIN 9 
12. LED PIN TO PIN 10  
13. DO NOT ALLOCATE D11 and D12 THAT WILL BE USED LATER FOR SERIAL COMMUNICATION 

* i have resistors and transistors kindly suggest whech sensor to connect  them to for accurate readings.
* and which sensors should be connected to 5v and 3.3v volts 

NOW WRITE THE CODE ACCORDING TO THE THINGS MENTIONED BELOW 

* ULTRASONIC SENSOR WILL BE USED FOR MONITORING THE WATER LEVEL OF THE TANK.
{ CONDITIONS:
THE SENSOR SHOULD PRINT OUT MESSAGES FIRSTLY PREVOUS LEVEL OF WATER IF THE WATER IS RISING AND WATER IS OVER FLOWING   THE WATER TANK IS 20CM IF THE WATER LEVEL IS ABOVE 17 PRINT WARNING THE WATER LEVEL IS FULL. IF THE READING GETS AFTER 30 CM THEN DONT PRINT OUT OUT OF RANGE 
}

* MQ2 SENSOR WILL BE USED TO DETECT GAS OR SMOKE IN THE HOUSE 
{ PRINT THE WARNING (GAS LEVEL INCREASING ALONG WITH THE SENSOR READINGSS AND THE BUZZER  WILL BE ACTIVATED FOR 5 SECONDS AND THEN SHUT OFF )
}

* DHT 11 SENSOR WILL BE USED FOR DETECTING THE TEMPERATURE OF THE ROOM 
{CONDITIONS THE SENSOR SHOULD PRINT THE TEMPERATURE READING TO CELISIUS AND THEN PRINT THE MESSAGE THE TEMPERATURE IS IF THE TEMPERATURE RISES PRINT THE TEMP IS RISING IN CELISUIS AND MAKE THE BUZZER GO BEEP FOR 3 SECONDS }

* SOIL MOISTURE SENSOR WILL BE USED TO TO DETECT WHEATHER THE SOIL IS DRY OR WET 
{CONDITIONS WHEN THE READING IS DRY PRINT THE MESSAGES THE SIOL IS DRY AND STARTING THE WATER PUMP AND THEN START THE WATER PUMP CONNECTED TO THE 2 CHANNEL RELAY WHEN THE SENSOR DETECT WETNESS PRINT MESSSAGE THE SOIL IS WET THE WATER PUMP IS TURNED OFF  }


* PIR SENSOR WILL BE USED TO DETECT MOTION IN THE ROOM 
{ CONDITIONS 
FIRST CALIBRATE THE PIR SENSOR FOR 10 SECONDS FOR ACCURATE READINGS & PRINT THE MESSAGE CALIBRATING THE PIR SENSOR.
WHEN THE MOTION IS DETECTED PRINT THE MESSAGE MOTION DETECTED !!!  AND LIGHT THE LED FOR 5 SECONDS THEN RESET THE PIR SENOR 
}

* IR SENSOR WILL BE INSTALLED IN THE DOOR OF THE HOUSE 
{ CONDITIONS 
IF THE VALUE IS 1 PRINT THE DOOR IS CLOSED WHEN THE VALUE IS 0 PRINT THE DOOR IS CLOSED  
}

PROVIDE ME WITH THE BEST CODE AND CODE LOGIC FOR THE ABOVE PROMPT AND STORE VARIABLES TO BE ACCESIBLE LATER and mention the   

additional info 
1. all the sensor readigs should print in the serial monitor along with its previous reading only if there is rise in readings of an sensor and it should only happen when there is a rise in readings otherwise just print the current readings 

2. store all the reading data in  variables clearly and mention it so it can be fetched by esp8266 via rx and tx pins later 

3. comment out the functionalties that send data variables via serial communication to be printed in esp8266's serial monitor

4. tell me how to upload code to both of the board enabling serial communiocation and data fetching in the prompt

5. do not print unable to read from dht sensor 

6. optimise the ir sensor for door opening and closing 
7. update dht readings regularly and do not create previous dht reading in the code for this sensor and dont print temperature rising unless it 50 degrees


                THE CODE OPTIMISED BY CHAT GPT prototyope 1 (trial)
// with unecessary printing of nan in tep                

#include <DHT.h>

const int DHTPin = 13;
const int MQ2Pin = A0;
const int soilMoisturePin = A1;
const int IRsensorPin = 2;
const int PIRsensorPin = 3;
const int trigPin = 4;
const int echoPin = 5;
const int relay1Pin = 6;
const int buzzerPin = 9;
const int ledPin = 10;

DHT dht(DHTPin, DHT11);

int waterLevel = 0;
int prevWaterLevel = 0;
int prevMQ2Value = 0;
int prevSoilMoisture = 0;
unsigned long prevMillis = 0;

const int GAS_THRESHOLD = 50; // Threshold for MQ2 sensor
const int MOISTURE_THRESHOLD = 500; // Threshold for soil moisture
const int HYSTERESIS = 100; // Hysteresis for soil moisture

void setup() {
  Serial.begin(9600);
  
  pinMode(MQ2Pin, INPUT);
  pinMode(IRsensorPin, INPUT);
  pinMode(PIRsensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(relay1Pin, LOW);
}

void loop() {
  int currentWaterLevel = measureWaterLevel();
  int currentMQ2Value = analogRead(MQ2Pin);
  int currentSoilMoisture = analogRead(soilMoisturePin);
  bool motionDetected = debounce(PIRsensorPin);
  int irValue = digitalRead(IRsensorPin);
  float temp = dht.readTemperature();

  Serial.print("Water Level: ");
  Serial.print(currentWaterLevel);
  Serial.println(" cm");

  Serial.print("MQ-2 Reading: ");
  Serial.println(currentMQ2Value);

  Serial.print("Soil Moisture: ");
  Serial.println(currentSoilMoisture);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C");
  
  if (temp > 50) {
    Serial.println("WARNING: Temperature exceeds 50°C!");
    activateBuzzer(3000);
  }

  if (currentWaterLevel > prevWaterLevel) {
    Serial.println("WARNING: Water level rising!");
  }

  if (abs(currentMQ2Value - prevMQ2Value) > GAS_THRESHOLD) {
    Serial.println("WARNING: Gas level increasing!");
    activateBuzzer(5000);
  }

  if (abs(currentSoilMoisture - prevSoilMoisture) > HYSTERESIS) {
    if (currentSoilMoisture > MOISTURE_THRESHOLD) {
      Serial.println("Soil is dry. Starting water pump.");
      digitalWrite(relay1Pin, HIGH);
      delay(1000); // Delay to ensure relay is activated
    } else {
      Serial.println("Soil is wet. Water pump turned off.");
      digitalWrite(relay1Pin, LOW);
      delay(1000); // Delay to ensure relay is deactivated
    }
  }

  if (motionDetected) {
    Serial.println("Motion detected!");
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
  }

  if (irValue == LOW) {
    Serial.println("Door is closed.");
  } else {
    Serial.println("Door is open.");
  }

  prevWaterLevel = currentWaterLevel;
  prevMQ2Value = currentMQ2Value;
  prevSoilMoisture = currentSoilMoisture;

  if (millis() - prevMillis >= 60000) { // Calibrate PIR sensor every minute
    Serial.println("Calibrating PIR sensor...");
    prevMillis = millis();
  }

  delay(2000); // Increase delay for displaying readings
}

int measureWaterLevel() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  int distance = duration * 0.034 / 2;
  if (distance < 0 || distance > 300) {
    Serial.println("Out of range for ultrasonic sensor.");
    return 0;
  }
  return distance;
}

void activateBuzzer(int duration) {
  tone(buzzerPin, 1000);
  delay(duration);
  noTone(buzzerPin);
}

bool debounce(int pin) {
  static unsigned long lastDebounceTime = 0;
  if (millis() - lastDebounceTime > 50) {
    lastDebounceTime = millis();
    return digitalRead(pin) == HIGH;
  }
  return false;
}


        THE CODE OPTIMISED BY CHAT GPT prototyope 2 (trial)

// TEMP NOT DISPLAYED IN THE CODE AFTER RISING 

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
  if (!isnan(temp) && abs(temp - previousTemp) >= 20) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("°C");

    if (temp > 30) {
      Serial.println("Temperature is above 30°C! Activating buzzer.");
      digitalWrite(BUZZERPIN, HIGH);
      delay(3000);
      digitalWrite(BUZZERPIN, LOW);
    }
    previousTemp = temp;
    // Store temp value for later use
  }

  // Read MQ2 sensor
  int gas = analogRead(MQ2PIN);
  Serial.print("Gas Level: ");
  Serial.println(gas);
  if (abs(gas - previousGas) >= 60) { // Adjust threshold for significant change
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



            PERFECT CODE (MAIN 1 TRIAL ARDUINO UNO)
//ALL THE THINGS WORKING PERFECTLY SOLELY 
// NO ESP8266 CONNECTIONS IS ESTABLISHED IN THIS CODE BUT IS INTEGRATED IN UPCOMING CODE {SERIAL COMMUNICATIONS}


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


1. Include functionalities of serial communication from arduino to esp8266 via serial communication 
2. provide me every pin connections needed to make serial communication happen 
3. update the code in such a way so that data[sensorreadings] can be fetched from arduino to esp8266 serial monitor  to be uploaded later to a service make suitable changes accordingly.
4. explain what is updated in code and in pin connection to establish serial communication .
5. provide complete code with added communication functionalities for arduino 
6. provide complete code with added communication functionalities for esp8266 
7. how to do all this 
8. provide full code for both


                                                  CGPT 3.5 (TRIAL 1)

To establish serial communication between an Arduino and an ESP8266, you can use the Serial interface (UART) available on both devices. Here's how you can achieve this:

Arduino Code Updates:
Serial Communication Setup:
We'll use the Serial interface to communicate with the ESP8266.
We'll send sensor readings to the ESP8266.
We'll add a unique identifier before each sensor reading to easily identify the data.

               



*              code  for   arduino   board 

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
  float temp = dht.readTemperature();
  Serial.print("A1:Temperature:");
  Serial.print(temp);
  Serial.println("°C");

  int gas = analogRead(MQ2PIN);
  Serial.print("A2:GasLevel:");
  Serial.println(gas);

  int soil = analogRead(SOILPIN);
  Serial.print("A3:SoilMoisture:");
  Serial.println(soil);

  int motion = digitalRead(PIRPIN);
  Serial.print("A4:MotionDetected:");
  Serial.println(motion);

  int door = digitalRead(IRPIN);
  Serial.print("A5:DoorStatus:");
  Serial.println(door);

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
    Serial.print("A6:WaterLevel:");
    Serial.print(distance);
    Serial.println("cm");
  }

  delay(2000);
}



*                         ESP8266   Code


void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // Read data from Arduino until newline character

    // Display only the data intended for the ESP8266
    if (data.startsWith("A1:") || data.startsWith("A2:") || data.startsWith("A3:") || 
        data.startsWith("A4:") || data.startsWith("A5:") || data.startsWith("A6:")) {
      Serial.println(data);  // Print the received data to ESP8266 serial monitor
    }
  }
}


* Explanation:

Arduino Code Updates:
Modified the data format sent over serial by adding a unique identifier (e.g., "A1:", "A2:", etc.) before each sensor reading.
The unique identifier allows the ESP8266 to identify and display only the data intended for it.

* ESP8266 Code:

Reads data from the Arduino through the serial interface.
Filters and displays only the data intended for the ESP8266 by checking the unique identifiers.

* Pin Connections:

Arduino:Connect TX (Transmit) of Arduino to RX (Receive) of ESP8266.

Connect RX (Receive) of Arduino to TX (Transmit) of ESP8266.

Make sure to connect the GND of both devices together.


* How to Do All This:
Upload the modified Arduino code to the Arduino board.
Connect the Arduino board and ESP8266 as per the pin connections mentioned above.
Upload the ESP8266 code to the ESP8266 board.
Open the Arduino serial monitor to see the sensor data formatted with the unique identifiers.
Open the ESP8266 serial monitor to see only the data intended for the ESP8266.
Remember to set the correct baud rate (9600 in this example) in both codes and serial monitors for successful communication.




              CHGPT CODE 2 


// PROBLEM INVERTED IR SENSING
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11

#define MQ2PIN A0
#define SOILPIN A1
#define IRPIN 2
#define PIRPIN 3
#define TRIGPIN 4
#define ECHOPIN 5
#define RELAY1 6
#define RELAY2 7
//#define SERVOPIN 8 // To be used later by RFID
#define BUZZERPIN 9
#define LEDPIN 10

#define WATER_TANK_MAX_LEVEL 20 // in cm
#define WATER_TANK_WARNING_LEVEL 17 // in cm

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  pinMode(PIRPIN, INPUT);
  pinMode(IRPIN, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  // Calibrating PIR sensor
  Serial.println("Calibrating PIR sensor...");
  delay(20000); // Calibrate for 20 seconds
  Serial.println("PIR sensor calibrated.");
}

void loop() {
  // Read DHT11 sensor
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("DHT11: Temperature: ");
  Serial.print(temp);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Read MQ2 gas sensor
  int gas = analogRead(MQ2PIN);
  Serial.print("MQ2: Gas Level: ");
  Serial.println(gas);

  // Read soil moisture sensor
  int soil = analogRead(SOILPIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soil);

  // Read PIR motion sensor
  int motion = digitalRead(PIRPIN);
  Serial.print("Motion Detected: ");
  Serial.println(motion ? "Yes" : "No");

  // Read IR sensor
  int door = digitalRead(IRPIN);
  Serial.print("Door Status: ");
  Serial.println(door ? "Closed" : "Open");

  // Read ultrasonic sensor for water level
  long duration, distance;
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = duration * 0.034 / 2;
  if (distance != 0 && distance <= WATER_TANK_MAX_LEVEL) {
    Serial.print("Water Level: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(2000); // Wait for 2 seconds before next reading
}
