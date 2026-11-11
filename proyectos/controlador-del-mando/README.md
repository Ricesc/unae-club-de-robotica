# Controlador del mando

Interfaz final del Explorador WiFi: dirección mediante teclado, ratón, pantalla táctil o gamepad, botones de encendido/apagado y control de velocidad.

`index.html` contiene sus estilos y JavaScript. El mismo HTML está incrustado en la cadena cruda de [`control.ino`](../explorador-wifi/control/control.ino). Si modificas la interfaz, mantén ambos contenidos sincronizados.

Puedes abrir el HTML para revisar la interfaz. Para controlar el robot, utiliza la página servida por el ESP8266: los comandos se envían mediante una petición relativa `./?var=...&velocidad=...`. Las fuentes tipográficas se cargan desde Google Fonts.

La sintaxis del JavaScript fue comprobada; no se ha probado esta actualización con hardware.
