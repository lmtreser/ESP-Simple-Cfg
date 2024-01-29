# Simple Portal Web para ESP8266

Simple portal web para configurar las credenciales de una red WiFi en un dispositivo construido alrededor de un ESP8266

## Documentación

#define ENABLE_DEBUG 1

// Credenciales WiFi
String wifiSsid = "ssid";
String wifiPassword = "password";

void wifiConnect();
void wifiAP();
void handleRoot();
void espSetup();
void espLoop();

#### Constantes

```
const int MAX_ATTEMPTS = 50;
const int RESET = 5;  // GPIO5 = D1
```

#### Archivo html.h

const char* htmlConfig PROGMEM = R"(

const char* htmlSuccess PROGMEM = R"(

## Recursos

- [Páginas embebidas con ESP8266 (WebServer)](https://blog.tute-avalos.com/2022/08/26/paginas-embebidas-webserver-esp8266/)
- [ESP8266 Pinout Reference: Which GPIO pins should you use?](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [ESP8266 Arduino Core ](https://arduino-esp8266.readthedocs.io/en/2.5.2/reference.html)
- [ESP8266WiFi library](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
