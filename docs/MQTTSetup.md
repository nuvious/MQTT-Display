# Setup MQTT

## Setup Proceedure

- Copy and rename `MQTTInfo_example.h` to `MQTTInfo.h` and change variables to match your MQTT configuration.

- Copy and rename `MQTTCallback_example.cpp` to `MQTTCallback.cpp`.

- Open the `esp32_tft_mqtt\ttgo_esp32_tft_mqtt.ino` sketch. Do not do this before renaming the above files or it will not work.

- Edit the mqtt_setup and mqtt_callback functions with the desired logic. By default the template just repeats the message to the serial interface.

- Connect TTGO LCD Display module via USB C.

- Open the serial monitor via Tools > Serial Monitor. Ensure it is set to 9600 baud.

- Upload the sketch to the module using Sketch > Upload, CTRL+U, or the Upload button.