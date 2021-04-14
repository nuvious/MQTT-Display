#ifndef MQTTINFO_H
#define MQTTINFO_H
static const char* WIFI_SSID = "YOUR SSID";           
static const char* WIFI_PASSWORD = "YOUR PASSWORD";
static const char* MQTT_HOST = "YOUR MQTT BROKER IP";
static int MQTT_PORT = 1883;
static int MQTT_KEEPALIVE_INTERVAL = 45;
static const char* MQTT_TOPIC = "YOUR MQTT TOPIC";
static const char* MQTT_CLIENT_ID = "mqtt_buzzer";
// Set username and password to null if not required
// for your mqtt broker.
static const char* MQTT_USER = "YOUR MQTT USER";
static const char* MQTT_PASSWORD = "YOUR MQTT PASSWORD";

// LED Pin
static const int OUTPUT_PIN = 4;
static const char* MQTT_DISPLAY_OFF = "off";

// Buzzer specific commands.
static const char* MQTT_SNOOZE = "snooze";
// static const int BUZZER_PIN = 12; // Use GPIO 12 for 3.3v buzzers (easier to solder)
static const int BUZZER_PIN = 27; // Use GPIO 27 for 5v buzzers (easier to solder)
static const int BUTTON_1 = 0;
static const int BUTTON_2 = 35;
static const int FREQ = 2000;
static const int CHANNEL = 0;
static const int RESOLUTION = 8;
static const int DUTY_CYCLE = 128;
#endif
