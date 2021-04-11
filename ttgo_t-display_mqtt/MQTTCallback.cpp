#include <Wire.h>
#include "MQTTCallback.h"

// int buzzerPin = 12; // 3v buzzers are easier to connect to GPIO 12
int buzzerPin = 27; // 5v buzzers are easier to connect to GPIO 27
int freq = 2000;
int channel = 0;
int resolution = 8;
int dutyCycle = 128;

const char* OFF_STRING = "off";

void mqtt_setup(){
  // Do setup here.
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(buzzerPin, channel);
}

void message_callback(String message){
  message.toLowerCase();
  if (message == OFF_STRING){
    ledcWrite(channel, 0);
  }else{
    ledcWrite(channel, dutyCycle);
  }
}
