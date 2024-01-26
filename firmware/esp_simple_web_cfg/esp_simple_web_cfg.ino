/*
    Simple Portal Web para ESP8266
    Permite configurar fácilmente el acceso a una red WiFi a un dispositivo IoT
*/

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "html.h"

const char* wifiSsid = "";
const char* wifiPassword = "";
const int BOTON = 5;  // GPIO5 = D1
bool buttonState;

ESP8266WebServer server{ 80 };

void handleRoot() {

  // Si llegan datos desde el formulario, ejecutar
  if (!(server.arg("ssid").isEmpty()) || !(server.arg("password").isEmpty())) {

    wifiSsid = server.arg("ssid").c_str();
    wifiPassword = server.arg("password").c_str();
    Serial.println(wifiSsid);
    Serial.println(wifiPassword);
    server.send(200, "text/html", htmlSuccess);

    delay(1000);
    WiFi.softAPdisconnect(true);  // Desconectar el modo AP
    WiFi.mode(WIFI_STA);          // Configurar como modo STATION
    wifiConnect();                // Conectar a WiFi
  }
  server.send(200, "text/html", htmlConfig);
}

// Funcionar en modo AP
void wifiAP() {

  WiFi.mode(WIFI_AP);
  Serial.println("Ejecutando en modo AP");
  while (!WiFi.softAP("ESP8266 WebServer")) {
    Serial.print('.');
    delay(100);
  }

  // WebServer atiende peticiones en '/'
  server.on("/", handleRoot);
  server.onNotFound([] {
    server.send(404, "text/plain", "Error 404");
  });
  server.begin();

  // Server ok
  Serial.print("Servidor iniciado en la IP: ");
  Serial.println(WiFi.softAPIP());
}

// Conectar a la red WiFi
void wifiConnect() {

  Serial.println("Ejecutando en modo STA");

  if (buttonState) {
    Serial.print("Conectado con el SSID: "  + WiFi.SSID());
    Serial.println(" y Password: " + WiFi.psk());
    WiFi.begin();
  } else {
    WiFi.begin(wifiSsid, wifiPassword);
  }

  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.print("\nConexión exitosa a la red WiFi con IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {

  pinMode(BOTON, INPUT_PULLUP);
  Serial.begin(9600);

  buttonState = digitalRead(BOTON);

  // De acuerdo al estado del botón de configuración hacer...
  if (buttonState) {
    wifiConnect();
  } else {
    wifiAP();
  }
}

void loop() {

  if (buttonState) {
    // Acá tu código una vez establecida la conexión
  } else {
    server.handleClient();  // Ejecución en modo AP
  }
}