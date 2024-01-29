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

// Credenciales WiFi
String wifiSsid = "ssid";
String wifiPassword = "password";

ESP8266WebServer server(80);

void wifiConnect();     // Conectar a la red WiFi
void wifiAP();          // Funcionar en modo AP
void handleRoot();      // Manejo de las peticiones desde el browser
void espSetup();        // Configuraciones, incluir dentro de setup()
void espLoop();         // Funciones auxiliares, incluir dentro de loop()

void wifiConnect() {

  int attempts = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSsid, wifiPassword);

#if ENABLE_DEBUG
  Serial.println("Ejecutando en modo STA");
  Serial.print("Conectado con el SSID: " + WiFi.SSID());
  Serial.println(" y Password: " + WiFi.psk());
#endif

  // Intentar conectar a WiFi
  while ((WiFi.status() != WL_CONNECTED) && (attempts < MAX_ATTEMPTS)) {
    delay(100);
#if ENABLE_DEBUG
    Serial.print(".");
#endif
    attempts++;
  }

  // Si no se logro la conexion, pasar al modo AP y lanzar el portal
  if (WiFi.status() != WL_CONNECTED) {
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

  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP("ESP8266 WebServer")) {
#if ENABLE_DEBUG
    Serial.print('.');
#endif
    delay(100);
  }

  // WebServer atiende peticiones en '/'
  server.on("/", handleRoot);
  server.onNotFound(handleRoot);
  server.begin();

#if ENABLE_DEBUG
  // Server ok
  Serial.print("Servidor iniciado en la IP: ");
  Serial.println(WiFi.softAPIP());
#endif
}

void handleRoot() {

  server.sendHeader("Location", "/", true);   // Redirigir al Captive Portal
  server.send(200, "text/html", htmlConfig);  // Enviar el Captive Portal

  // Si llegan datos desde el formulario, ejecutar
  if (!(server.arg("ssid").isEmpty()) || !(server.arg("password").isEmpty())) {

    wifiSsid = server.arg("ssid").c_str();
    wifiPassword = server.arg("password").c_str();
    server.send(200, "text/html", htmlSuccess);
    delay(2000);

    WiFi.softAPdisconnect(true);  // Desconectar el modo AP
    wifiConnect();                // Conectar a WiFi
  }
}

// Incluir dentro de setup()
void espSetup() {

#if ENABLE_DEBUG
  Serial.begin(9600);
#endif
  pinMode(RESET, INPUT_PULLUP);
  wifiConnect();  // Conectar a WiFi
}

// Incluir dentro de loop()
void espLoop() {

  server.handleClient();  // Ejecución en modo AP

  // Resetear las credenciales almacenadas
  bool buttonState = digitalRead(RESET);
  if (buttonState == LOW) WiFi.disconnect(true);
}

#endif