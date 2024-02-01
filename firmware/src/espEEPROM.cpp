/*
 *  espEEPROM.cpp
 *  Gestión de la memoria EEPROM interna
 *  created 31 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#include "espWebCfg.h"

// Direcciones EEPROM a utilizar
const uint8_t SSID_ADDRESS = 0;
const uint8_t PASS_ADDRESS = 100;

// Leer un String desde la memoria EEPROM interna
String readString(uint8_t address) {
  
  String result = "";
  char c;

  for (uint8_t i = 0; (c = EEPROM.read(address + i)) != '\0'; i++) {
    result += c;
  }
  return result;
}

// Escribir un String en la memoria EEPROM interna
void writeString(uint8_t address, const String &data) {
  for (uint8_t i = 0; i < data.length(); i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + data.length(), '\0');
  // Para hacer efectivo los cambios, es necesario hacer un commit() 
  EEPROM.commit();
}

// Almacenar las credenciales WiFi en la memoria EEPROM interna
void saveCredentials(const String &ssid, const String &password) {
  writeString(SSID_ADDRESS, ssid);
  writeString(PASS_ADDRESS, password);
}