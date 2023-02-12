#include <Arduino.h>
#include <Homie.h>
#include "ambilight.h"
#include "pulse.h"


#define BRAND "FlashDOORs"
#define FW_NAME "illuminated"
#define FW_VER "1.2.0"

void onHomieEvent(const HomieEvent &event){
  switch (event.type){
    case HomieEventType::WIFI_CONNECTED:
      Serial << "Wi-Fi connected: " << (int8_t)event.wifiReason << endl;
    break;
    case HomieEventType::MQTT_READY:
      Serial << "MQTT connected: " << (int8_t)event.mqttReason << endl;
    break;
    case HomieEventType::WIFI_DISCONNECTED:
      Serial << "Wi-Fi disconnected, reason: " << (int8_t)event.wifiReason << endl;
    break;
    case HomieEventType::MQTT_DISCONNECTED:
      Serial << "MQTT disconected, reason: " << (int8_t)event.mqttReason << endl;
    break;
    default:
    break;
  }
}

ambilightNode AmbilightNode("ambilight", "Ambilight", "WS2812B");
pulseNode PulseNode("buttons", "ISR", "interrupt");

void setup() {
  Serial.begin(115200);
  Serial << endl
         << endl;
  Homie_setBrand(BRAND);
  Homie_setFirmware(FW_NAME, FW_VER);
  Homie.onEvent(onHomieEvent);
  AmbilightNode.ambilightSetup();
  PulseNode.pulseSetup();
  Homie.setup();
}

void loop() {
  Homie.loop();
}
