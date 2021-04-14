#include <Wire.h>
#include <PubSubClient.h>
#include <TFT_eSPI.h>
#include "MQTTCallback.h"
#include "MQTTInfo.h"
#include <Button2.h>

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

static TFT_eSPI* tft;
static PubSubClient* client;


void update_screen(String text){
  // Clear screen.
  tft->fillScreen(TFT_BLACK);

  // Print text; will default to white text.
  tft->setTextSize(2);
  tft->setCursor(0, 0, 2);
  tft->print(text);
}

void sound_alarm(){
  // Turn on the backlight
  digitalWrite(OUTPUT_PIN, HIGH);

  // Sound the buzzer.
  ledcWrite(CHANNEL, DUTY_CYCLE);
}

void dismiss(){
  // Silence the buzzer
  ledcWrite(CHANNEL, 0);
  
  // Shut off the backlight.
  digitalWrite(OUTPUT_PIN, LOW);
}

void snooze(Button2& btn){
  Serial.println("Snooze");
  dismiss();
  client->publish(MQTT_TOPIC, MQTT_SNOOZE);
}

void mqtt_setup(PubSubClient* client_instance, TFT_eSPI* tft_instance){
  // Setup display pin and shut off backlight.
  // Initialize TFT
  client = client_instance;
  tft = tft_instance;
  tft->setRotation(1);
  update_screen("MQTT Alarm");
  
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  
  // Do setup here.
  ledcSetup(CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(BUZZER_PIN, CHANNEL);

  // Setup button functions.
  btn1.setReleasedHandler(snooze);

  btn2.setReleasedHandler(snooze);
}

void mqtt_loop(){
  btn1.loop();
  btn2.loop();
}

void message_callback(String message){
  // Update the message on the screen before setting it to lower case.
  update_screen(message);

  // Set message to lower case.
  message.toLowerCase();

  // If the message is not the off message, print it.
  if (message != MQTT_DISPLAY_OFF && message != MQTT_SNOOZE) {
    sound_alarm(message);
  }else{
    dismiss();
  }

  // Ensure output pin is set to output.
  pinMode(OUTPUT_PIN, OUTPUT);
}
