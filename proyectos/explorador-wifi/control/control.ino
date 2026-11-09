#include <ESP8266WiFi.h>

const char* ssid = "TU_RED_WIFI";
const char* password = "TU_CLAVE_WIFI";
/*
const char* ssid = "TU_RED_WIFI";
const char* password = "TU_CLAVE_WIFI";
*/
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  // Configuración del GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  /*
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a red: ");
  Serial.println(ssid);
   */
  WiFi.begin(ssid, password); // Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  /*
  Serial.println("");
  Serial.println("WiFi conectado");
  */
  server.begin(); // Iniciamos el servidor
  /*
  Serial.println("Servidor Iniciado");
  Serial.println("Ingrese desde un navegador web usando la siguiente IP:");
  */
  //importante, aqui da la ip del sitio web
  //Serial.println(WiFi.localIP()); // Obtenemos la IP
  
}

void loop() {
  WiFiClient client = server.available();
  if (client) { // Si hay un cliente presente
    //Serial.println("Nuevo Cliente");
    
    // Esperamos hasta que hayan datos disponibles
    while (!client.available() && client.connected()) {
      delay(1);
    }
    
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('\r');
    //Serial.println(linea1);

    // Envía los datos según los botones presionados
    if (linea1.indexOf("var=of") != -1) { // Buscamos un LED=ON en la 1° Línea
      digitalWrite(2, HIGH);
    }
    if (linea1.indexOf("var=on") != -1) { // Buscamos un LED=OFF en la 1° Línea
      digitalWrite(2, LOW);
    }
    if (linea1.indexOf("var=a") != -1) { // Botón Avanzar presionado
      Serial.write('a');
    }
    if (linea1.indexOf("var=d") != -1) { // Botón Izquierda presionado
      Serial.write('d');
    }
    if (linea1.indexOf("var=e") != -1) { // Botón Detener presionado
      Serial.write('e');
    }
    if (linea1.indexOf("var=c") != -1) { // Botón Derecha presionado
      Serial.write('c');
    }
    if (linea1.indexOf("var=b") != -1) { // Botón Reversa presionado
      Serial.write('b');
    }
    
    client.flush(); 
                
    //Serial.println("Enviando respuesta...");   
    // Encabezado HTTP    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close"); // La conexión se cierra después de finalizar de la respuesta
    client.println();
    
    // Página HTML para el navegador
    client.println(R"(<!DOCTYPE html>
<html lang='es'>
    <head>
        <meta charset='UTF-8' />
        <meta name='viewport' content='width=device-width, initial-scale=1.0' />
        <title>Mando</title>
        <style>
            @import url('https://fonts.googleapis.com/css2?family=Concert+One&family=Varela+Round&display=swap');

            h1,
            .contenedor-velocidad * {
                font-family: 'Concert One', sans-serif;
                font-weight: 400;
                font-style: normal;
                text-wrap: balance;
            }

            h1 {
                text-align: center;
                color: white;
            }

            body {
                display: flex;
                flex-direction: column;
                align-items: center;
                justify-content: center;
                height: 100vh;
                margin: 0;
                gap: 25px;
                background: #00c6ff;
                background: -webkit-linear-gradient(
                    top,
                    #1e5799 0%,
                    #00c6ff 25%,
                    #26c6da 55%,
                    #7ae3ef 100%
                );
                background: linear-gradient(
                    to bottom,
                    #1e5799 0%,
                    #00c6ff 25%,
                    #26c6da 55%,
                    #7ae3ef 100%
                );
            }

            button {
                font-weight: 600;
            }

            .led {
                display: flex;
                justify-content: space-between;
                width: 150px;
            }

            .led button {
                padding: 10px 20px;
                border: none;
                border-radius: 5px;
                color: white;
                font-size: 16px;
                cursor: pointer;
            }

            .on-btn {
                background-color: #4caf50;
                transition: background-color 0.2s, box-shadow 0.2s;
            }

            .off-btn {
                background-color: #f44336;
            }

            .controller {
                position: relative;
                width: 200px;
                height: 200px;
                border-radius: 50%;
                border: 4px solid #ccc;
                display: flex;
                justify-content: center;
                align-items: center;
                background-color: rgb(41 102 155);
            }

            .controller button {
                position: absolute;
                width: 50px;
                height: 50px;
                border: none;
                color: white;
                font-size: 14px;
                cursor: pointer;
            }

            .controller button:not(.stop-btn) {
                border-radius: 10px;
                background-color: #03a9f4;
            }

            .controller .stop-btn {
                background-color: #ff9800;
                border-radius: 50%;
                width: 60px;
                height: 60px;
            }

            .avanzar-btn {
                top: 10px;
            }

            .reversa-btn {
                bottom: 10px;
            }

            .izquierda-btn {
                left: 10px;
            }

            .derecha-btn {
                right: 10px;
            }

            .avanzar-btn.active {
                background-color: #0288d1 !important;
                box-shadow: inset 0 3px 6px rgba(0, 0, 0, 0.5);
            }

            .reversa-btn.active {
                background-color: #0288d1 !important;
                box-shadow: inset 0 3px 6px rgba(0, 0, 0, 0.5);
            }

            .izquierda-btn.active {
                background-color: #0288d1 !important;
                box-shadow: inset 0 3px 6px rgba(0, 0, 0, 0.5);
            }

            .derecha-btn.active {
                background-color: #0288d1 !important;
                box-shadow: inset 0 3px 6px rgba(0, 0, 0, 0.5);
            }

            .stop-btn.active {
                background-color: #f57c00 !important;
                box-shadow: inset 0 3px 6px rgba(0, 0, 0, 0.5);
            }

            .contenedor-velocidad {
                display: flex;
                flex-direction: column;
                font-weight: 600;
                align-items: center;
            }
        </style>
    </head>

    <body>
        <h1>CLUB DE ROBÓTICA</h1>
        <div class='led'>
            <button class='on-btn'>On</button>
            <button class='off-btn'>Off</button>
        </div>
        <div class='controller'>
            <button class='avanzar-btn' data-command='a'>▲</button>
            <button class='reversa-btn' data-command='b'>▼</button>
            <button class='izquierda-btn' data-command='d'>◄</button>
            <button class='derecha-btn' data-command='c'>►</button>
            <button class='stop-btn' data-command='e'>STOP</button>
        </div>
        <div class='contenedor-velocidad'>
            <input
                type='range'
                name='velocidad'
                id='velocidad'
                min='0'
                value='1'
                max='10'
                step='1'
            />
            <label for='velocidad'>velocidad</label>
            <p><span id='velocidad-value'>1</span>/10</p>
        </div>
        <script>
            // Asignación de botones a las teclas correspondientes
            const buttons = {
                ArrowUp: document.querySelector('.avanzar-btn'),
                ArrowDown: document.querySelector('.reversa-btn'),
                ArrowLeft: document.querySelector('.izquierda-btn'),
                ArrowRight: document.querySelector('.derecha-btn'),
                Space: document.querySelector('.stop-btn'),
            };

            // Botones de encendido y apagado
            const ON_BTN = document.querySelector('.on-btn');
            const OFF_BTN = document.querySelector('.off-btn');

            // Control de la velocidad
            const VELOCIDAD_RANGE = document.getElementById('velocidad');
            const NIVEL_VELOCIDAD = document.getElementById('velocidad-value');
            let currentSpeed = VELOCIDAD_RANGE.value;

            // Comando de stop y variables de control
            const STOP_COMMAND = 'e';
            let lastCommand = '';
            let stopTimeout;
            const STOP_DELAY = 300; // Tiempo para enviar el stop tras la última acción

            // Función para enviar un comando
            function sendCommand(command) {
                if (command !== lastCommand) {
                    fetch(`./?var=${command}&velocidad=${currentSpeed}`)
                        .then((response) =>
                            console.log(
                                'Comando enviado:',
                                command,
                                'velocidad:',
                                currentSpeed
                            )
                        )
                        .catch((error) =>
                            console.error('Error al enviar comando:', error)
                        );
                    lastCommand = command; // Actualiza el último comando enviado
                }
            }

            // Función que envía el comando de stop después del intervalo
            function scheduleStop() {
                clearTimeout(stopTimeout); // Cancela cualquier timeout anterior
                stopTimeout = setTimeout(() => {
                    sendCommand(STOP_COMMAND); // Enviar el stop después de STOP_DELAY
                }, STOP_DELAY);
            }

            // Manejar la pulsación de teclas
            function handleKeyDown(event) {
                const button = buttons[event.code];
                if (button) {
                    button.classList.add('active');
                    sendCommand(button.dataset.command);
                }
            }

            // Manejar la liberación de teclas
            function handleKeyUp(event) {
                const button = buttons[event.code];
                if (button) {
                    button.classList.remove('active');
                    sendCommand(STOP_COMMAND); // Enviar comando de stop al soltar
                }
            }

            // Manejo de clic de los botones del control
            function handleMouseDown(event) {
                const button = event.currentTarget;
                button.classList.add('active');
                sendCommand(button.dataset.command);
            }

            function handleMouseUp(event) {
                const button = event.currentTarget;
                button.classList.remove('active');
                sendCommand(STOP_COMMAND); // Enviar comando de stop al soltar
            }

            // Asignar eventos de teclado
            document.addEventListener('keydown', handleKeyDown);
            document.addEventListener('keyup', handleKeyUp);

            // Asignar eventos a los botones de control
            Object.values(buttons).forEach((button) => {
                button.addEventListener('mousedown', handleMouseDown);
                button.addEventListener('mouseup', handleMouseUp);
                button.addEventListener('touchstart', handleMouseDown, {
                    passive: true,
                });
                button.addEventListener('touchend', handleMouseUp, {
                    passive: true,
                });
            });

            // Asignar eventos de clic a los botones de encendido/apagado
            ON_BTN.addEventListener('mousedown', () => sendCommand('on'));
            OFF_BTN.addEventListener('mousedown', () => sendCommand('off'));

            // Función para mapear valores del joystick a comandos de dirección
            function getGamepadDirection(gamepad) {
                const THRESHOLD = 0.5; // Umbral para considerar el movimiento

                const axisX = gamepad.axes[0]; // Eje X (Izquierda/Derecha)
                const axisY = gamepad.axes[1]; // Eje Y (Arriba/Abajo)

                // Determinar dirección basada en los ejes
                if (axisY < -THRESHOLD) {
                    return 'a'; // Avanzar
                } else if (axisY > THRESHOLD) {
                    return 'b'; // Reversa
                } else if (axisX < -THRESHOLD) {
                    return 'd'; // Izquierda
                } else if (axisX > THRESHOLD) {
                    return 'c'; // Derecha
                } else {
                    return STOP_COMMAND; // Stop si no hay movimiento significativo
                }
            }

            // Función principal para actualizar el estado del gamepad
            function updateGamepad() {
                const gamepads = navigator.getGamepads();
                if (gamepads[0]) {
                    const gamepad = gamepads[0];
                    const direction = getGamepadDirection(gamepad);

                    // Si se detecta un movimiento, enviar el comando de dirección y reiniciar el temporizador de stop
                    if (direction !== STOP_COMMAND) {
                        sendCommand(direction);
                        scheduleStop(); // Programar el stop después de un periodo de inactividad
                    }
                }

                requestAnimationFrame(updateGamepad); // Continuar actualizando el estado del gamepad
            }

            // Detectar conexión de un gamepad
            window.addEventListener('gamepadconnected', (event) => {
                console.log('Gamepad conectado:', event.gamepad);
                requestAnimationFrame(updateGamepad); // Comenzar a actualizar el estado del gamepad
            });

            // Detectar desconexión de un gamepad
            window.addEventListener('gamepaddisconnected', (event) => {
                console.log('Gamepad desconectado:', event.gamepad);
            });

            // Actualizar el nivel de velocidad al cambiar el rango
            VELOCIDAD_RANGE.addEventListener('input', function (e) {
                currentSpeed = e.target.value;
                NIVEL_VELOCIDAD.textContent = currentSpeed;
            });
        </script>
    </body>
</html>
)");
    
    delay(1);
    //Serial.println("Respuesta enviada");
    //Serial.println();
  }
}
