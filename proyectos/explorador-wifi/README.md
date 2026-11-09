# Explorador WiFi

- **Qué es:** prototipo de robot con interfaz web de dirección y velocidad, control mediante teclado, pantalla táctil y mando.
- **Origen:** proyecto del Club de Robótica UNAE.
- **Tecnología:** Arduino/C++, ESP8266WiFi, SoftwareSerial, Servo, HTML y JavaScript.
- **Estado:** prototipo académico; no se verificó la compilación ni el funcionamiento con hardware en esta actualización.
- **Relacionado:** [interfaz web inicial del mando](../controlador-del-mando/index.html).

## Cómo abrirlo

Los sketches se cargan por separado en sus placas correspondientes:

| Archivo | Función |
|---|---|
| `control/control.ino` | Servidor web del ESP8266 e interfaz de control |
| `proyecto_2_wifi/proyecto_2_wifi.ino` | Recepción de comandos por comunicación serie y movimiento de los servos |

Abre cada archivo en Arduino IDE con la placa y bibliotecas que corresponden a sus declaraciones `#include`. Revisa los pines y la conexión serie antes de conectarlos; este repositorio no incluye un esquema de cableado verificado.

## Configuración WiFi

`control/control.ino` contiene únicamente los marcadores `TU_RED_WIFI` y `TU_CLAVE_WIFI`, tanto en la configuración activa como en el ejemplo comentado. Configura los valores de tu red solo en tu copia local antes de cargar el firmware. No incluyas esos cambios ni credenciales reales en commits o publicaciones.

La lógica del programa se conserva; los cambios de configuración sustituyen únicamente los valores WiFi por estos marcadores.
