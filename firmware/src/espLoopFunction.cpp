/*
 *  espLoopFunction.cpp
 *  Manejo de funciones auxiliares
 *  created 31 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#include "espWebCfg.h"

// Constantes
const uint8_t RESET = 4;            // Pin de reset de credenciales, GPIO4 = G4 = D2
const uint16_t BLINK_TIME = 3000;   // Tiempo entre destellos LED "Status"
const uint8_t FLASH_LED = 100;      // Tiempo de destello LED "Status"

// Función para hacer destellar el LED "Status"
void blinkLed() {
  
  static bool statusLed = true;
  static uint32_t lastMillis = 0;
  uint32_t currentMillis = millis();

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

// Manejo de funciones auxiliares, incluir dentro de loop()
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