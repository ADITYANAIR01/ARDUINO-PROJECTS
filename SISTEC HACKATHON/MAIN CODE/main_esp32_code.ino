#include <HTTPClient.h>
#include <WiFi.h>
const char* ssid = "POCO";
const char* password = "123456789";
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi");
    delay(1000);
  }
  Serial.println("Connected");
}

void loop() {
  if (Serial.available() > 0)
  {
    String url = Serial.readString();
    //Serial.println(url);
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
  delay(100);
}
