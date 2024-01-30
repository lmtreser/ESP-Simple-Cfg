/*
 *  html.h
 *  Captive Portal Embebido
 *  created 29 Ene 2024
 *  Lucas Martin Treser (github: @lmtreser)
 *
*/

#ifndef html_h
#define html_h

const char* htmlConfig PROGMEM = R"(
  <!DOCTYPE html>
  <html lang="es">
    <head>
      <meta charset="UTF-8"/>
      <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
      <title>ESP8266 WebServer Config</title>
      <style>
        /* Estilos generales del formulario */
        form {  
          max-width: 400px;
          margin: 0 auto;
          padding: 20px;
          border: 1px solid #ccc;
          border-radius: 5px;
        }
        /* Estilos para los campos de entrada */
        input {
          width: 100%;
          padding: 10px;
          margin-bottom: 15px;
          box-sizing: border-box;
          border: 1px solid #ccc;
          border-radius: 3px;
        }
        /* Estilos para el encabezado */
        h1 {
          text-align: center;
          color: #333;
        }
        /* Estilos para el párrafo */
        p {
          text-align: center;
          color: #666;
        }
        /* Estilos para el botón de envío */
        button {
          width: 100%;
          padding: 10px;
          background-color: #4caf50;
          color: #fff;
          border: none;
          border-radius: 3px;
          cursor: pointer;
        }
      </style>
    </head>
    <body>
      <h1>Simple Portal Web para ESP8266</h1>
      <p>Ingresar los datos de la red WiFi a la que se desea conectar:</p>
      <form action="/" method="post">
        <input type="text" name="ssid" maxlength="30" placeholder="SSID"/><br/>
        <input type="text" name="password" maxlength="30" placeholder="Password"/><br/>
        <input type="submit" value="Guardar"/>
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
      <style>
        /* Estilos para el div */
        div {
          border: 1px solid #ccc;
          border-radius: 3px;
        }
        /* Estilos para el h2 */
        h2 {
          text-align: center;
          color: #333;
        }
        /* Estilos para el h3 */
        h3 {
          text-align: center;
          color: #666;
        }
      </style>
    </head>
    <body>
      <h2>¡Cambios guardados con exito!</h2>
      <h3>Reiniciando...</h3>
    </body>
  </html>)";

#endif