/*
    Simple Portal Web para ESP8266
    Permite configurar fácilmente el acceso a una red WiFi a un dispositivo IoT
    La IP por defecto para conectarse es 192.168.4.1
*/

#include "espWebcfg.h"

void setup() {

  espSetupFunction(); // Configuraciones WiFi

}

void loop() {

  espLoopFunction();

  /*
      Acá tu código...
      Considerar no utizar retardos bloqueantes (delay).
  */
}