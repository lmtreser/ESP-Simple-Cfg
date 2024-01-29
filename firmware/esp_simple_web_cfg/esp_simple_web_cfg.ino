/*
    Simple Portal Web para ESP8266
    Permite configurar fácilmente el acceso a una red WiFi a un dispositivo IoT
    La IP por defecto para conectarse es 192.168.4.1
*/

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "espSetup.h"
#include "html.h"

const char* wifiSsid = "";
const char* wifiPassword = "";

const int MAX_ATTEMPTS = 50;
const int RESET = 5;  // GPIO5 = D1

ESP8266WebServer server(80);

// Conectar a la red WiFi
void wifiConnect() {

  int attempts = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSsid, wifiPassword);

  Serial.println("Ejecutando en modo STA");
  Serial.print("Conectado con el SSID: " + WiFi.SSID());
  Serial.println(" y Password: " + WiFi.psk());

  // Intentar conectar a WiFi
  while ((WiFi.status() != WL_CONNECTED) && (attempts < MAX_ATTEMPTS)) {
    delay(100);
    Serial.print(".");
    attempts++;
  }

  // Si no se logro la conexion, pasar al modo AP y lanzar el portal
  if (WiFi.status() != WL_CONNECTED) {
    wifiAP();
  } else {
    Serial.print("\nConexión exitosa a la red WiFi con IP: ");
    Serial.println(WiFi.localIP());
  }
}

// Funcionar en modo AP
void wifiAP() {

  Serial.println("Ejecutando en modo AP");

  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP("ESP8266 WebServer")) {
    Serial.print('.');
    delay(100);
  }

  // WebServer atiende peticiones en '/'
  server.on("/", handleRoot);
  server.onNotFound(handleRoot);
  server.begin();

  // Server ok
  Serial.print("Servidor iniciado en la IP: ");
  Serial.println(WiFi.softAPIP());
}

void handleRoot() {

  server.sendHeader("Location", "/", true);  // Redirigir al Captive Portal
  server.send(200, "text/html", htmlConfig); // Enviar el Captive Portal

  // Si llegan datos desde el formulario, ejecutar
  if (!(server.arg("ssid").isEmpty()) || !(server.arg("password").isEmpty())) {

    wifiSsid = server.arg("ssid").c_str();
    wifiPassword = server.arg("password").c_str();
    server.send(200, "text/html", htmlSuccess);

    //delay(1000);
    WiFi.softAPdisconnect(true);  // Desconectar el modo AP
    wifiConnect();                // Conectar a WiFi
  }
}

void setup() {

  Serial.begin(9600);
  pinMode(RESET, INPUT_PULLUP);

  // Conectar a WiFi
  wifiConnect();
}

void loop() {

  server.handleClient();  // Ejecución en modo AP

  // Resetear las credenciales almacenadas
  bool buttonState = digitalRead(RESET);
  if (buttonState == LOW) WiFi.disconnect(true);
}