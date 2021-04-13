#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "MQTTInfo.h"
#include "MQTTCallback.h"

static TFT_eSPI tft = TFT_eSPI();
static PubSubClient client;

IPAddress local_ip;
WiFiClient espClient;

void setup(void) {
  // Start serial port.
  Serial.begin(115200);

  // Minimal initialization
  // Further settings should be set in MQTTCallback.cpp in the mqtt_setup.
  tft.init();

  // Connect to Wifi/MQTT
  setup_wifi();
  client.setClient(espClient);
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);

  // Call callback specific setup.
  mqtt_setup(&client, &tft);
}

void setup_wifi() {
  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  // Connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  local_ip = WiFi.localIP();
}

void loop() {
  // If not connected to wifi reconnect.
  if(WiFi.status() != WL_CONNECTED){
    setup_wifi();
  }
  
  // If not connected to mqtt, reconnect.
  if (!client.connected()) {
    reconnect();
  }
  
  // Run MQTT client loop.
  client.loop();
  mqtt_loop();
}

void callback(char* topic, byte* message, unsigned int length) {
  // Make a raw copy and a lowercase copy of the string.
  String payload;
  for (int i = 0; i < length; i++) {
    payload += (char)message[i];
  }

  // Call the message callback with the raw string.
  message_callback(payload);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
