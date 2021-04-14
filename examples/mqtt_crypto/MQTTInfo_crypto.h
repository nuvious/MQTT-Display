#ifndef MQTTINFO_H
#define MQTTINFO_H
static const char* WIFI_SSID = "YOUR SSID";           
static const char* WIFI_PASSWORD = "YOUR PASSWORD";
static const char* MQTT_HOST = "YOUR MQTT BROKER IP";
static int MQTT_PORT = 1883;
static int MQTT_KEEPALIVE_INTERVAL = 45;
static const char* MQTT_TOPIC = "YOUR MQTT TOPIC";
static const char* MQTT_CLIENT_ID = "mqtt_crypto";
// Set username and password to null if not required
// for your mqtt broker.
static const char* MQTT_USER = "YOUR MQTT USER";
static const char* MQTT_PASSWORD = "YOUR MQTT PASSWORD";

// LED Pin
static const int OUTPUT_PIN = 4;
static const char* MQTT_DISPLAY_OFF = "off";

// Crypto endpoint; don't edit these.
// https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD,EUR
static const char* ENDPOINT = "https://min-api.cryptocompare.com/data/price";
static const char* QUERY_1 = "?fsym=";
static const char* QUERY_2 = "&tsyms=";

// Cryptocurrency symbol
static const char* SYMBOL = "ETH";
// Comma separated list of price currencies.
static const char* CURRENCY = "USD,EUR";
// How often to poll (ms)
static unsigned int POLL_FREQUENCY = 30000;
#endif