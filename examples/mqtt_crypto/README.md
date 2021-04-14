# MQTT Crypto

Simple MQTT application that gets the current price of a particular crypto currency and displays the prices on the display and publishes a json result to MQTT_TOPIC/SYMBOL (example 'esp32/crypto/eth').

## Libraries

In addition to the libraries required in the root project [README](../../README.md), you'll need to install the [HTTPClient](https://github.com/amcewen/HttpClient) library by searching for it under Sketch > Include Library > Manage Libraries.

## Deploy Example

- Copy `MQTTCallback_crypto.cpp` to the `ttgo_t-display_mqtt` folder and rename it to `MQTTCallback.cpp.`
- Copy `MQTTInfo_crypto.h` to the `ttgo_t-display_mqtt` folder and rename it to `MQTTInfo.h`.
- Edit the `MQTTInfo.h` to setup wifi, your MQTT broker info, your symbol and price currencies of choice.
- Compile/Upload to your TTGO T-Display or similar module.
- You should see the symbol and the prices for that symbol display on the screen. If not check the serial console (default 115200 baud) for debug info.
