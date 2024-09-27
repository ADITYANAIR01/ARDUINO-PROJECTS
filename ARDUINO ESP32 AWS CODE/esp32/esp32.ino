#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

#define RXD2 16
#define TXD2 17

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage(String data)
{
  StaticJsonDocument<400> doc;
  char jsonBuffer[512];
  
  String values[9];
  int valueIndex = 0;
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == ',') {
      valueIndex++;
    } else {
      values[valueIndex] += data.charAt(i);
    }
  }

  doc["water_level"] = values[0];
  doc["motion"] = values[1];
  doc["temperature"] = values[2];
  doc["fire"] = values[3];
  doc["lpg"] = values[4];
  doc["ir_sensor"] = values[5];
  doc["tilt"] = values[6];
  doc["vibration"] = values[7];
  doc["light"] = values[8];

  serializeJson(doc, jsonBuffer);

  if (client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer)) {
    Serial.println("Message published successfully");
  } else {
    Serial.println("Failed to publish message");
  }
}

void messageHandler(char* topic, byte* payload, unsigned int length) {
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  connectAWS();
}

void loop() {
  if (!client.connected()) {
    connectAWS();
  }

  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Received from Arduino: " + data);
    publishMessage(data);
  }
  
  client.loop();
  delay(1000);
}