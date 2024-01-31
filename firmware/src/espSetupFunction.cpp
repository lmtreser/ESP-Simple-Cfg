/*
 *  espSetupFunction.cpp
 *  Gestión de funciones de configuración
 *  created 31 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#include "espWebCfg.h"

// Configuraciones, incluir dentro de setup()
void espSetup() {

#if ENABLE_DEBUG
  Serial.begin(9600);
#endif
  pinMode(RESET, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  EEPROM.begin(511);

  // Al iniciar recuperar las credenciales desde la EEPROM
  wifiSsid = readString(SSID_ADDRESS);
  wifiPassword = readString(PASS_ADDRESS);
  wifiConnect();
}