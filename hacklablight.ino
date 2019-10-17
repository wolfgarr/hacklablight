#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

/*  ESP8266 LDR ArduinoIDE https example code
 * 
 *  Based on: https://vaasa.hacklab.fi/2016/02/06/esp8266-on-nodemcu-board-ds18b20-arduinoide-thingspeak/
 *  ESP8266 Witty: http://www.schatenseite.de/en/2016/04/22/esp8266-witty-cloud-module/
 */

#include "LightStatusHandler.h"
#include "conf.h"

const int LDR_PIN = A0;

// minimum sensor reading when lights are considered ON
const int minOn = 950;

// maximum sensor reading when lights are considered OFF
const int maxOff = 700;

unsigned long lastMillis = 0;
unsigned int loopInterval = 5*1000;

LightStatusHandler lightStatusHandler(minOn, maxOff);

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);

  connectToWifi();
}

void loop() {
  if (millis() - lastMillis > loopInterval) {
    lastMillis = millis();
    if(WiFi.status() != WL_CONNECTED) {
      connectToWifi();
    }

    int lights = analogRead(LDR_PIN);

    if (lightStatusHandler.hasChanged(lights)) {
      sendStatus(lightStatusHandler.statusToString());
    }
  }
}

void sendStatus(String status) {
  HTTPClient http;
  http.begin(url, httpsFingerprint);
  http.addHeader("Content-Type", "application/json");

  Serial.println(status);

  int httpCode = http.POST(status);
  String payload = http.getString();

  Serial.println(http.errorToString(httpCode));
  http.end();
}

void connectToWifi() {
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
