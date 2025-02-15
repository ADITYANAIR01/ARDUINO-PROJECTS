#include <SoftwareSerial.h>

#define IR_PIN 2
#define RX_PIN 13
#define TX_PIN 12

SoftwareSerial espSerial(RX_PIN, TX_PIN); // RX, TX

void setup() {
  pinMode(IR_PIN, INPUT);
  espSerial.begin(9600); // Communication with ESP32
}

void loop() {
  int ir_status = digitalRead(IR_PIN);
  if (ir_status == 1) {
    espSerial.println("The door is opened");
  } else {
    espSerial.println("The door is closed");
  }
  delay(1000);
}
