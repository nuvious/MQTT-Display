/*
#include <Wire.h>
#include <PubSubClient.h>
#include <TFT_eSPI.h>
#include "MQTTCallback.h"
#include "MQTTInfo.h"

static TFT_eSPI* tft;
static PubSubClient* client;

void update_screen(String text){
  // Clear screen.
  tft->fillScreen(TFT_BLACK);

  // Print text; will default to white text.
  tft->setTextSize(1);
  tft->setCursor(0, 0, 2);
  tft->print(text);
}

void mqtt_setup(PubSubClient* client_instance, TFT_eSPI* tft_instance){
  // Setup display pin and shut off backlight.
  // Initialize TFT
  client = client_instance;
  tft = tft_instance;

  // Set rotation and turn backlight off
  tft->setRotation(1);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  
  // Add additional logic here.
}

void mqtt_loop(){
  // Add loop specific logic here.
}

void message_callback(String message){
  // Update the message on the screen.
  update_screen(message);

  // Set message to lower case.
  message.toLowerCase();

  // If the message is not the off message, print it.
  if (message != MQTT_DISPLAY_OFF) {
    // Turn on the backlight
    digitalWrite(OUTPUT_PIN, HIGH);
  }else{
    // Shut off the backlight.
    digitalWrite(OUTPUT_PIN, LOW);
  }

  // Ensure output pin is set to output.
  pinMode(OUTPUT_PIN, OUTPUT);
}
*/
