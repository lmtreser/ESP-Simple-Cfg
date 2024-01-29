#ifndef html_h
#define html_h

const char* htmlConfig PROGMEM = R"(
  <!DOCTYPE html>
  <html lang='es'>
    <head>
      <meta charset='UTF-8'>
      <meta name='viewport' content='width=device-width, initial-scale=1.0'>
      <title>ESP8266 WebServer Config</title>
    </head>
    <body>
      <h1>Simple Portal Web para ESP8266</h1>
      <p>Ingresar los datos de la red WiFi a la que se desea conectar:</p>
      <form action='/' method='post'>
        <input type='text' name='ssid' maxlength='30' placeholder='SSID'><br>
        <input type='text' name='password' maxlength='30' placeholder='Password'><br>
        <input type='submit' value='Guardar'>
      </form>
    </body>
  </html>)";

const char* htmlSuccess PROGMEM = R"(
  <!DOCTYPE html>
  <html lang='es'>
    <head>
      <meta charset='UTF-8'>
      <meta name='viewport' content='width=device-width, initial-scale=1.0'>
      <title>ESP8266 WebServer Config</title>
    </head>
    <body>
      <h2>Cambios guardados con exito.</h2>
      <h3>Reiniciando...</h3>
    </body>
  </html>)";

#endif