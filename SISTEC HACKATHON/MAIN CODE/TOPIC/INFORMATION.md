    Title: IoT Sensor Integration Project Prompt

Description:
Create an IoT system incorporating various sensors to monitor environmental conditions and security aspects within a premises.
Sensors include flame, PIR motion, gas, soil moisture, IR, and ultrasonic sensors. The objective is to develop a robust monitoring 
system capable of detecting hazards and environmental changes, and providing timely alerts to users.

Sensors and Their Functions:

    Flame Sensor:
Function: Detects flames and triggers alerts for fire hazards.

    PIR Motion Sensor:
Function: Monitors occupancy and detects significant motion for security purposes.

    Gas Sensor:
Function: Monitors gas levels and alerts users in case of gas leaks or hazardous concentrations.

    Soil Moisture Sensor:
Function: Measures soil moisture levels to automate irrigation systems.

    IR Sensor:
Function: Installed on doors to detect opening and closing events for security monitoring.

    Ultrasonic Sensor (Water Level Sensing):
Function: Installed in water tank to measure water levels. Alerts user when water reaches a certain level.

*   PIN CONNECTIONS T-1

    Flame Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Signal: Connect to pin 2.

    PIR Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Signal: Connect to pin 3.

    Gas Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Analog Output: Connect to Arduino's Analog pin A1.

    Moisture Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Analog Output: Connect to Arduino's Analog pin A2.

    IR Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Signal: Connect to pin 7.

    Ultrasonic Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Trigger Pin: Connect to pin 4.
Echo Pin: Connect to pin 5.

    DHT11 Temperature and Humidity Sensor:

VCC: Connect to Arduino's 5V pin.
GND: Connect to Arduino's GND pin.
Data: Connect to pin 6.

    Buzzer:

VCC: Connect to Arduino's 5V pin.   Signal: Connect to pin 12.
GND: Connect to Arduino's GND pin.

* PROVIDE THE CODE INCLUDING THE PINS LOCATION ABOVE TO ARDUINO UNO BOARD 
* WITH PROPER LIBRARIES
* PROVIDE ME WITH A VERY OPTIMIZED CODE THAT INCLUDES INTELLIGENT CLASS AND OBJECTS 

* THINGS TO CONSIDER 

* IR SENSOR IS TO BE INSTALLED IN A PHYSICAL DOOR WHICH IS 5 CM AWAY FROM SENSOR.IF THE DISTANCE EXCEEDS 8 CENTIMETERS W PRINT OUT THE MESSAGE IN SERIAL MONITOR OF ARDUINO 
* FLAME SENSOR IS TO BE USED TO DETECT FIRE,THE FLAME BUZZER MUST ONLY SET THE BUZZER SOUND WHEN THE FLAME IS DETECTED.AND WHEN THE FLAMES IS DETECTED THE BUZZER SHOULD BEEP PRINTING THE MESSAGE OF " FIRE DETECTED !!! "
* GAS SENSOR IS TO BE USED FOR DETECTING GAS AND SMOKE IN THE ENVIORNMENT. THE BUZZER SHOULD GO BEEP ONLY WHEN GAS/SMOKE IS DETECTED OTHERWISE THE BUZZER SHOULD BE SILENCED.
* DHT 11 TEMPERATURE SENSOR IS USED TO DETECT THE CHAGE OF TEMEPERATURE AND MAKE THE BUZZER GO BEEP ONLY WHEN THERE IS A SUDDEN RISE IN TEMPERATURE.
* ULTRASONIC SENSOR IS TO BE USED AS AN WATER LEVEL DETECTOR WHEN THE WATER REACHES A CERTAIN POINT THE BUZZER WILL GO BEEP PRINTING THE MESSAGE "THE WATER TANK IS FULL".
* PIR SENSOR IS USED TO DETECT BIG MOVEMENTS INSIDE THE HOUSE AND NOT SMALL MOVEMENTS IT SHOULD NOT HAVE ACESS TO BUZZER BY ANY MEANS.


*   THINGS TO PROVIDE

* SIMPLIFIED PIN CONNECTIONS TO ARDUINO UNO R3 
* FULL,SIMPLIFIED,OPTIMIZED AND SMART CODE THAT INCLUDES THE MAKING OF CLASSES AND OBLJECTS OF SENSOR 
* THE FULL  CODE SHOULD BE ERRORLESS
* ADDITIONAL TIPS TO IMPROVE ANYTHING IN THIS PROMPT
