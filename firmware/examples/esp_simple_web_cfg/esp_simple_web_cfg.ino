/*
    Simple Portal Web para ESP8266/ESP32
    Permite configurar fácilmente el acceso a una red WiFi a un dispositivo IoT
    La IP por defecto para conectarse es 192.168.4.1
*/

#include "espWebCfg.h"

void setup() {

  espSetup(); // Configuraciones WiFi

}

void loop() {

  espLoop();

  /*
      Acá tu código...
      Considerar no utizar retardos bloqueantes (delay).
  */
}
