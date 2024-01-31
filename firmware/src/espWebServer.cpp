/*
 *  espWebServer.cpp
 *  Gestión del WebServer
 *  created 31 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#include "espWebCfg.h"

bool wifiMode = false; // Modo de funcionamiento
ESP8266WebServer server(80);

// Funcionar en modo AP
void wifiAP() {

#if ENABLE_DEBUG
  Serial.println("Ejecutando en modo AP");
#endif

  wifiMode = true;  // Flag de modo AP
  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP("ESP8266 WebServer")) {
#if ENABLE_DEBUG
    Serial.print('.');
#endif
    delay(100);
  }

  // WebServer atiende peticiones en '/'
  server.on("/", HTTP_GET, handleRootGET);
  server.on("/", HTTP_POST, handleRootPOST);
  server.onNotFound(handleRootGET);
  server.begin();

#if ENABLE_DEBUG
  // Server ok
  Serial.print("Servidor iniciado en la IP: ");
  Serial.println(WiFi.softAPIP());
#endif
}

// Enviar el Captive Portal
void handleRootGET() {
  server.send(200, "text/html", htmlConfig);
}

// Manejo de las peticiones desde el browser
void handleRootPOST() {

  // Si llegan datos desde el formulario, ejecutar
  // ToDo: validar los datos ingresados
  if (!(server.arg("ssid").isEmpty()) || !(server.arg("password").isEmpty())) {

    wifiSsid = server.arg("ssid").c_str();
    wifiPassword = server.arg("password").c_str();
#if ENABLE_DEBUG
    Serial.println("Datos desde el formulario: ");
    Serial.println("SSID: " + wifiSsid);
    Serial.println("Password: " + wifiPassword);
#endif
    saveCredentials(wifiSsid, wifiPassword);
    server.send(200, "text/html", htmlSuccess);
#if ENABLE_DEBUG
    Serial.println("Datos guardados en la EEPROM.");
    Serial.println("Reiniciando el ESP8266");
#endif

    delay(3000);
    wifiMode = false;
    ESP.restart();
  }
}