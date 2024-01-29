# Simple Portal Web para ESP8266

Simple portal web para configurar las credenciales de una red WiFi en un dispositivo construido alrededor de un ESP8266.

Se trata de un pequeño [Captive Portal](https://en.wikipedia.org/wiki/Captive_portal) que permite configurar las credenciales WiFi (SSID y Password) a un *usuario final* que tenga algún dispositivo IoT basado en el microcontrolador ESP8266.

## Documentación

Para compilar el proyecto son necesarias las siguientes dependencias:

- [ESP8266WebServer.h](https://github.com/esp8266/ESPWebServer)
- [ESP8266WiFi.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- [EEPROM.h](https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM)

### Archivo "espSetup.h"

Activar el modo de depuración vía Serial, 1=activado 0=desactivado

`#define ENABLE_DEBUG 1`

Objetos string que almacenan las credenciales WiFi

```
String wifiSsid = "ssid";
String wifiPassword = "password";
```

Conectar a la red WiFi

`void wifiConnect();     // `
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

## ToDo

- Agregar soporte para micros ESP32
- Validar los datos ingresados mediante los campos del formulario
- Mejorar el diseño del portal HTML
- Documentar variantes de hardware

## Recursos

- [Páginas embebidas con ESP8266 (WebServer)](https://blog.tute-avalos.com/2022/08/26/paginas-embebidas-webserver-esp8266/)
- [ESP8266 Pinout Reference: Which GPIO pins should you use?](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [ESP8266 Arduino Core ](https://arduino-esp8266.readthedocs.io/en/2.5.2/reference.html)
- [ESP8266WiFi library](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
