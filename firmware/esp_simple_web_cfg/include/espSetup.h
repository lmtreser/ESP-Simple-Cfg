/*
 *  espSetup.h
 *  Gestión de la conexión WiFi
 *  created 29 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#ifndef espSetup_h
#define espSetup_h

// 1 para activar el DEBUG por Serial
#define ENABLE_DEBUG 1

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "espEEPROM.h"
#include "html.h"

// Constantes
const int MAX_ATTEMPTS = 50;  // Intentos de conexion
const int RESET = 5;          // Pin de reset de credenciales, GPIO5 = D1
const int BLINK_TIME = 3000;   // Tiempo LED Status
const int FLASH_LED = 100;

// Credenciales WiFi
String wifiSsid = "ssid";
String wifiPassword = "password";

// Variables, modo de funcionamiento
bool wifiMode = false;

ESP8266WebServer server(80);

void wifiConnect();     // Conectar a la red WiFi
void wifiAP();          // Funcionar en modo AP
void handleRootGET();   // Enviar el Captive Portal
void handleRootPOST();  // Manejo de las peticiones desde el browser
void espSetup();        // Configuraciones, incluir dentro de setup()
void espLoop();         // Funciones auxiliares, incluir dentro de loop()
void blinkLed();        // Función para hacer destellar el Status LED

void wifiConnect() {

  int attempts = 0;

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

void handleRootGET() {
  server.send(200, "text/html", htmlConfig);  // Enviar el Captive Portal
}

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

void blinkLed() {
  
  static bool statusLed = true;
  static unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis >= BLINK_TIME) {
    lastMillis = currentMillis;
    statusLed = !statusLed;
    digitalWrite(LED_BUILTIN, statusLed);
  }

  if ((statusLed == false) && (currentMillis - lastMillis >= FLASH_LED)) {
    statusLed = !statusLed;
    digitalWrite(LED_BUILTIN, statusLed);
  }
}

// Incluir dentro de setup()
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
  wifiConnect();  // Conectar a WiFi
}

// Incluir dentro de loop()
void espLoop() {

  // Ejecución sólo en modo AP
  if (wifiMode == true) {
    server.handleClient();  
  } else {

      // Ejecución en caso de desconexión de la red WiFi
      if (WiFi.status() != WL_CONNECTED) {
#if ENABLE_DEBUG
        Serial.println("Conexion perdida. Reconectando...");
#endif
        wifiConnect();
      }

      blinkLed(); // Blink Status LED (100ms cada 3s)

      // Si se pulsa, invocar el Captive Portal
      bool buttonState = digitalRead(RESET);
      if (buttonState == LOW) wifiAP();
    }
}

#endif