#include <Wire.h>
#include <PubSubClient.h>
#include <TFT_eSPI.h>
#include "MQTTCallback.h"
#include "MQTTInfo.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>

static TFT_eSPI* tft;
static PubSubClient* client;
static HTTPClient http;

void update_screen(String text){
  // Clear screen.
  tft->fillScreen(TFT_BLACK);

  // Print text; will default to white text.
  tft->setTextSize(2);
  tft->setCursor(0, 0, 2);
  tft->print(text);
}

String get_crypto_data(){
  // Construct server path.
  String serverPath = "";
  serverPath += ENDPOINT;
  serverPath += QUERY_1;
  serverPath += SYMBOL;
  serverPath += QUERY_2;
  serverPath += CURRENCY;

  
  http.begin(serverPath.c_str());
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  String payload;
  if (httpResponseCode == 200) {
    // If the response 200, pass the payload.
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
  }else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    payload = "";
  }
  // Free resources
  http.end();
  return payload;
}

void mqtt_setup(PubSubClient* client_instance, TFT_eSPI* tft_instance){
  // Setup display pin and shut off backlight.
  // Initialize TFT
  client = client_instance;
  tft = tft_instance;
  tft->setRotation(1);
  update_screen("MQTT Crypto");
  
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  
  // No further setup required.
}

void mqtt_loop(){
  // Get the crypto payload.
  String crypto_payload = get_crypto_data();

  // If it's not the empty string.
  if(crypto_payload.length() > 0){
    JSONVar myObject = JSON.parse(crypto_payload);
  
    // Parse the json
    if (JSON.typeof(myObject) == "undefined") {
      update_screen("Error");
      Serial.println("Parsing input failed!");
      return;
    }
    Serial.print("JSON object = ");
    Serial.println(myObject);
  
    // Get keys from response.
    JSONVar keys = myObject.keys();

    // Start constructing the display string.
    String text = SYMBOL;
    text += '\n';

    // Loop through currencies in json response.
    for (int i = 0; i < keys.length(); i++) {
      // Convert JSONVar to standard c-types.
      const char* symbol = keys[i];
      double price = (double)myObject[keys[i]];

      // Construct price string.
      text += symbol;
      text += " = ";
      text += price;
      text += '\n';
    }

    // Publish the raw json to the MQTT Topic
    String topic = "";
    topic += MQTT_TOPIC;
    topic += "/";
    topic += SYMBOL;
    client->publish(topic.c_str(), crypto_payload.c_str());

    // Display the price info on the TFT
    update_screen(text);
  }else{
    update_screen("Error");
  }
  delay(POLL_FREQUENCY);
}

void message_callback(String message){
  // Not used in this example.
}