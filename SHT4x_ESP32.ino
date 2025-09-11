#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoOTA.h>
#include "Adafruit_SHT4x.h"
#include <Wire.h>

const char* ssid = "temperatetech24g";
const char* password = "06940836";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT Topics
const char* mqtt_topic_sensor1_temp = "esp32/sensor1/temp";
const char* mqtt_topic_sensor1_humidity = "esp32/sensor1/humidity";
const char* mqtt_topic_sensor2_temp = "esp32/sensor2/temp";
const char* mqtt_topic_sensor2_humidity = "esp32/sensor2/humidity";
const char* mqtt_topic_sensor3_temp = "esp32/sensor3/temp";
const char* mqtt_topic_sensor3_humidity = "esp32/sensor3/humidity";
const char* mqtt_topic_sensor4_temp = "esp32/sensor4/temp";
const char* mqtt_topic_sensor4_humidity = "esp32/sensor4/humidity";

WiFiClient espClient;
PubSubClient client(espClient);

#define PCAADDR 0x70
#define SHT4x_I2C_BUSES 4

Adafruit_SHT4x sht4_sensors[SHT4x_I2C_BUSES];

void selectI2CBus(uint8_t busIndex) {
  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << busIndex);
  Wire.endTransmission();
}

void initializeSensor(uint8_t busIndex, Adafruit_SHT4x& sensor) {
  selectI2CBus(busIndex);
  if (!sensor.begin()) {
    Serial.print("Couldn't find SHT4x on bus ");
    Serial.println(busIndex);
    delay(1000);
    sensor.begin();
  }
  sensor.setPrecision(SHT4X_HIGH_PRECISION);
  sensor.setHeater(SHT4X_NO_HEATER);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  WiFi.begin(ssid, password);

  for (uint8_t i = 0; i < SHT4x_I2C_BUSES; i++) {
    initializeSensor(i, sht4_sensors[i]);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // OTA Setup
  ArduinoOTA.setHostname("ESP32_SHT4x");
  ArduinoOTA.setPassword("coldeasy");
  ArduinoOTA.onStart([]() {
    Serial.println("Start OTA update");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd OTA update");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  ArduinoOTA.handle();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  for (uint8_t i = 0; i < SHT4x_I2C_BUSES; i++) {
    readAndPublishSensorData(i, sht4_sensors[i]);
  }
  delay(2000);  // Publish every 2 seconds
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_SHT4x")) {
      Serial.println("connected");
      client.publish("esp32/status", "ESP32 reconnected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void readAndPublishSensorData(uint8_t busIndex, Adafruit_SHT4x& sensor) {
  selectI2CBus(busIndex);
  sensors_event_t humidity, temp;
  sensor.getEvent(&humidity, &temp);
  char tempStr[10], humidityStr[10];
  snprintf(tempStr, sizeof(tempStr), "%.2f", temp.temperature);
  snprintf(humidityStr, sizeof(humidityStr), "%.2f", humidity.relative_humidity);

  // Publish to MQTT
  if (busIndex == 0) {
    client.publish(mqtt_topic_sensor1_temp, tempStr);
    client.publish(mqtt_topic_sensor1_humidity, humidityStr);
  } else if (busIndex == 1) {
    client.publish(mqtt_topic_sensor2_temp, tempStr);
    client.publish(mqtt_topic_sensor2_humidity, humidityStr);
  } else if (busIndex == 2) {
    client.publish(mqtt_topic_sensor3_temp, tempStr);
    client.publish(mqtt_topic_sensor3_humidity, humidityStr);
  } else if (busIndex == 3) {
    client.publish(mqtt_topic_sensor4_temp, tempStr);
    client.publish(mqtt_topic_sensor4_humidity, humidityStr);
  }

  // Send data to backend
  sendDataToBackend(temp.temperature, humidity.relative_humidity, busIndex + 1);

  // Debug print
  Serial.print("Sensor ");
  Serial.print(busIndex + 1);
  Serial.print(": Temp=");
  Serial.print(tempStr);
  Serial.print("°C, Humidity=");
  Serial.print(humidityStr);
  Serial.println("%");
}

void sendDataToBackend(float temp, float humidity, uint8_t sensorId) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://192.168.1.25:5000/api/sensor-data";
    String payload = "{\"sensorId\": \"sensor" + String(sensorId) + "\", \"temperature\": " + String(temp) + ", \"humidity\": " + String(humidity) + "}";
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      Serial.print("Data sent to backend for sensor ");
      Serial.print(sensorId);
      Serial.println(" successfully");
    } else {
      Serial.print("Error sending data to backend for sensor ");
      Serial.print(sensorId);
      Serial.println(": ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}

