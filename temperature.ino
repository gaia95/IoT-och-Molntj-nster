#include <WiFi.h>
#include <ESPmqttclient.h>

#define WIFI_SSID "WIFI NAME"
#define WIFI_PASSWORD "WIFI PASSWORD"

#define IOT_HUB_FQDN "IoTHub name.azure-devices.net"
#define DEVICE_ID "DEVICE ID"
#ifndef USE_X509_CERT
#define DEVICE_KEY "DEVICE KEY"
#endif

#define TELEMETRY_FREQUENCY_MILLISECS 2000

const int temperaturePin = 34;

static bool hasWiFi = false;

ESPmqttclient mqttClient;

void setup() {
  Serial.begin(115200);
  pinMode(temperaturePin, INPUT);

  hasWiFi = initializeWiFi();
  if (!hasWiFi) {
    Serial.println("WiFi initialization failed");
    return;
  }

  // Set up MQTT client
  mqttClient.begin(IOT_HUB_FQDN, 8883, DEVICE_ID, DEVICE_KEY);
}

void loop() {
  if (hasWiFi) {
    mqttClient.loop();

    if (millis() % TELEMETRY_FREQUENCY_MILLISECS == 0) {
      float temperature = readTemperature();
      sendTelemetry(temperature);
    }

    delay(10);
  }
}

bool initializeWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  int attemptCounter = 0;
  while (WiFi.status() != WL_CONNECTED && attemptCounter < 30) {
    delay(500);
    Serial.print(".");
    attemptCounter++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    return true;
  } else {
    Serial.println("Failed to connect to WiFi");
    return false;
  }
}

float readTemperature() {
  int sensorValue = analogRead(temperaturePin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  return temperature;
}

void sendTelemetry(float temperature) {
  char telemetryData[256];
  sprintf(telemetryData, "{\"temperature\":%.2f}", temperature);

  // Publish telemetry message
  mqttClient.publish("devices/" DEVICE_ID "/messages/events/", telemetryData);
}

