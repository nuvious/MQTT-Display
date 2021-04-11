#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "MQTTInfo.h"
#include "MQTTCallback.h"

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

IPAddress local_ip;

WiFiClient espClient;
PubSubClient client;

void setup(void) {
  // Start serial port.
  Serial.begin(9600);

  // Initialize TFT
  tft.init();
  tft.setRotation(1);

  // Connect to MQTT
  setup_wifi();
  client.setClient(espClient);
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);

  // Call callback specific setup.
  mqtt_setup();

  // Setup display pin and shut off backlight.
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
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
}

void update_screen(String text){
  // Clear screen.
  tft.fillScreen(TFT_BLACK);

  // Print text; will default to white text.
  tft.setTextSize(2);
  tft.setCursor(0, 0, 2);
  tft.print(text);
}

void callback(char* topic, byte* message, unsigned int length) {
  // Make a raw copy and a lowercase copy of the string.
  String messageRaw, messageTemp;
  for (int i = 0; i < length; i++) {
    messageRaw += (char)message[i];
    messageTemp += (char)tolower(message[i]);
  }

  // If the off message is received shut off the display.
  if(messageTemp == MQTT_DISPLAY_OFF){
    Serial.println(MQTT_DISPLAY_OFF);
    update_screen("");
    digitalWrite(OUTPUT_PIN, LOW);
  }else{
    digitalWrite(OUTPUT_PIN, HIGH);
    update_screen(messageRaw);
  }
  pinMode(OUTPUT_PIN, OUTPUT);

  // Call the message callback with the raw string.
  message_callback(messageRaw);
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
