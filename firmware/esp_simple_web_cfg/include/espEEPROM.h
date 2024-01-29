/*
 *  espEEPROM.h
 *  Gestión de la memoria EEPROM interna
 *  created 29 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#ifndef espEEPROM_h
#define espEEPROM_h

#include <EEPROM.h>

// Direcciones EEPROM a utilizar
const int SSID_ADDRESS = 0;
const int PASS_ADDRESS = 100;

void writeString(int address, const String &data);                 // Escribir un String en la memoria EEPROM interna
String readString(int address);                                    // Leer un String desde la memoria EEPROM interna
void saveCredentials(const String &ssid, const String &password);  // Almacenar las credenciales WiFi en la memoria EEPROM interna

void writeString(int address, const String &data) {
  for (int i = 0; i < data.length(); i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + data.length(), '\0');
  EEPROM.commit();
}

String readString(int address) {
  String result = "";
  char c;

  for (int i = 0; (c = EEPROM.read(address + i)) != '\0'; i++) {
    result += c;
  }
  return result;
}

void saveCredentials(const String &ssid, const String &password) {
  writeString(SSID_ADDRESS, ssid);
  writeString(PASS_ADDRESS, password);
}

#endif
