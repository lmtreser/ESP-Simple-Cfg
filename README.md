# Simple Portal Web para ESP8266

Simple portal web para configurar las credenciales de una red WiFi en un dispositivo construido alrededor de un ESP8266

## Documentación

Dependencias: #include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

archivo espSetup.h

// 1 para activar el DEBUG por Serial
#define ENABLE_DEBUG 1

// Credenciales WiFi
String wifiSsid = "ssid";
String wifiPassword = "password";

void wifiConnect();     // Conectar a la red WiFi
void wifiAP();          // Funcionar en modo AP
void handleRootGET();   // Enviar el Captive Portal
void handleRootPOST();  // Manejo de las peticiones desde el browser
void espSetup();        // Configuraciones, incluir dentro de setup()
void espLoop();         // Funciones auxiliares, incluir dentro de loop()

// Constantes
const int MAX_ATTEMPTS = 50;  // Intentos de conexion
const int RESET = 5;          // Pin de reset de credenciales, GPIO5 = D1
```
```

#### Archivo html.h

const char* htmlConfig PROGMEM = R"(
const char* htmlSuccess PROGMEM = R"(

archivo espEEPROM.h

// Direcciones EEPROM a utilizar
const int SSID_ADDRESS = 0;
const int PASS_ADDRESS = 100;

void writeString(int address, const String &data);                 // Escribir un String en la memoria EEPROM interna
String readString(int address);                                    // Leer un String desde la memoria EEPROM interna
void saveCredentials(const String &ssid, const String &password);  // Almacenar las credenciales WiFi en la memoria EEPROM interna

## Recursos

- [Páginas embebidas con ESP8266 (WebServer)](https://blog.tute-avalos.com/2022/08/26/paginas-embebidas-webserver-esp8266/)
- [ESP8266 Pinout Reference: Which GPIO pins should you use?](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [ESP8266 Arduino Core ](https://arduino-esp8266.readthedocs.io/en/2.5.2/reference.html)
- [ESP8266WiFi library](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
