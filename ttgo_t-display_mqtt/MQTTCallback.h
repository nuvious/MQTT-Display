void mqtt_setup(PubSubClient* client_instance, TFT_eSPI* tft_instance);
void mqtt_loop();
void message_callback(String message);
