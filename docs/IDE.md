# DEV Environment Setup

## IDE Setup

- Download Arduino IDE
- Add board manager via Preferences > Additional Board Manager URLs

  - [esp32 board manager url](https://dl.espressif.com/dl/package_esp32_index.json)

- Add esp32 via Tools > Board > Board manager. Search for esp32 and install.

- Install TFT and Button Libraries by searching for them in Sketch > Include Library > Manage Libraries

  - [TFT_eSPI Library](https://github.com/Bodmer/TFT_eSPI)
  - [Button2 Library](https://github.com/LennartHennigs/Button2)
  - [PubSubClient](https://pubsubclient.knolleary.net/)

- Edit %USERPROFILE%\Documents\Arduino\libraries\TFT_eSPI\User_Setup_select.h and comment out `#include <User_Setup.h>` and add the line `#include <User_Setups/TTGO_T_Display.h>`.

- Download and install [CP210x_Universal_Windows_Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) and install via device manager. After install the device should show up in device manager under Port. Note the COMX number; ex COM4.

- Set the following parameters under Tools
 - Board > ESP32 Dev Module
 - Flash Size > 4MB
 - PSRAM > Disabled
 - Port > COMX Port in Device Manager