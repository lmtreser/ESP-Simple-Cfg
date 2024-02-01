/*
 *  espWebCfg.h
 *  Cabecera principal
 *  created 29 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#ifndef ESPWEBCFG_H
#define ESPWEBCFG_H

#ifdef ESP8266
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <Arduino.h>
#include <EEPROM.h>

#define ENABLE_DEBUG 1  // DEBUG por Serial, 1=activado

extern const uint8_t MAX_ATTEMPTS;
extern const uint8_t SSID_ADDRESS;
extern const uint8_t PASS_ADDRESS;
extern const uint8_t RESET;
extern const uint8_t FLASH_LED;
extern const uint16_t BLINK_TIME;

extern const char* htmlConfig;
extern const char* htmlSuccess;

extern bool wifiMode;
extern String wifiSsid;
extern String wifiPassword;

#ifdef ESP8266
extern ESP8266WebServer server;
#elif defined(ESP32)
extern WebServer server;
#endif

void wifiConnect();     // Conectar a la red WiFi
void wifiAP();          // Funcionar en modo AP
void handleRootGET();   // Enviar el Captive Portal
void handleRootPOST();  // Manejo de las peticiones desde el browser
void espSetup();        // Configuraciones, incluir dentro de setup()
void espLoop();         // Funciones auxiliares, incluir dentro de loop()
void blinkLed();        // Función para hacer destellar el Status LED

String readString(uint8_t address);                                 // Leer un String desde la memoria EEPROM interna
void writeString(uint8_t address, const String &data);              // Escribir un String en la memoria EEPROM interna
void saveCredentials(const String &ssid, const String &password);   // Almacenar las credenciales WiFi en la memoria EEPROM interna

#endif