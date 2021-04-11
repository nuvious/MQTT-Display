#include <Wire.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "MQTTCallback.h"

void mqtt_setup(){
  pinMode(OUTPUT_PIN, OUTPUT);
}

void message_callback(String message){
  Serial.print("Message: ");
  Serial.println(message);
}
