 *    FOR ESP 32 DEV BOARD 

1. INSTALL CP210X WINDOWS DRIVERS 
https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads 

2. PLUG THE ESP32 DEV MODULE IN THE COMPUTER

3. CHECK THE DEVICE MANAGER FOR ACCURATE PORT SELECTION 

4. IN ARDUINO IDE GO TO BOARD MANAGER AND TYPE ESP32 BY ESPRESSIF SYSTEMS , INSTALL IT.

5. GO TO FILE PREFERENCES AND THE THE FOLLOWING LINK 
https://espressif.github.io/arduino-esp32/package_esp32_index.json

6. SELECT ESP32 DEV MODULE WITH ITS CORRECT PORT/COM

7. START BY VERIFING THE CODE AND UPLOAD IT.

8. AFTER THE CODE COMPILES HOLD DOWN BOOT BUTTON IF THE ESP32 TO COMPLETE UPLOADING OF THE CODE 

    
     
  *   FOR NODE MCU (ESP 8266)

1. Install esptool
    * pip install esptool

2. Install CH340G DRIVERS 

3. Go to prefrences and change the boards additional manager to install driver node mcu -:
    * https://arduino.esp8266.com/stable/package_esp8266com_index.json 

4. Go to tools board and select the board connected 
    * Node MCU 
(if COM PORT not detected try to replug the usb and see change in ports) 

5. Go to device manager and verify the com port 