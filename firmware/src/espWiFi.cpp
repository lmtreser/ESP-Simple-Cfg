/*
 *  espWiFi.cpp
 *  Gestión de la conexión WiFi
 *  created 31 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#include "espWebCfg.h"

// Intentos de conexion máximos (multiplicador de tiempo)
const uint8_t MAX_ATTEMPTS = 50;

// Credenciales WiFi
String wifiSsid = "ssid";
String wifiPassword = "password";

// Conectar a la red WiFi
void wifiConnect() {

  uint8_t attempts = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSsid, wifiPassword);

#if ENABLE_DEBUG
  Serial.println("Ejecutando en modo STA");
  Serial.print("Conectado con el SSID: " + WiFi.SSID());
  Serial.println(" y Password: " + WiFi.psk());
#endif

  // Intentar conectar a WiFi (durante 5 segundos)
  while ((WiFi.status() != WL_CONNECTED) && (attempts < MAX_ATTEMPTS)) {
    delay(100);
#if ENABLE_DEBUG
    Serial.print(". ");
#endif
    attempts++;
  }

  // Si no se logro la conexion, pasar al modo AP y lanzar el portal
  if (WiFi.status() != WL_CONNECTED) {
#if ENABLE_DEBUG
    Serial.println("\nSin conexión WiFi. Lanzando el Captive Portal.");
#endif    
    wifiAP();
  } else {
#if ENABLE_DEBUG
    Serial.print("\nConexión exitosa a la red WiFi con IP: ");
    Serial.println(WiFi.localIP());
#endif
  }
}