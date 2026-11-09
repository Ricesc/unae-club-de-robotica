#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(2, 3); // RX, TX
Servo servo1, servo2; // Asume que se están usando las librerías Servo para controlar los servos
char ultimoComando = '\0'; // Variable para almacenar el último comando recibido

int left=45;
int right=45;
int tiempo=50;
int left_start=55;
int right_start=35;
int left_end=35;
int right_end=55;

void setup() {
  Serial.begin(9600); // Inicializa el puerto Serial para el Monitor Serie
  mySerial.begin(9600); // Inicializa SoftwareSerial
  
  servo1.attach(4);
  servo2.attach(6);
  servo1.write(left);
  servo2.write(right);
  Serial.println("Inicio del programa"); // Mensaje inicial
}

void loop() {

  if (mySerial.available() > 0) {
    char var = mySerial.read();
    Serial.print("Comando recibido: ");
    Serial.println(var);
    mySerial.flush();  // Limpia el buffer después de leer

    if (var != ultimoComando) { // Solo procesa si el comando es nuevo
      ultimoComando = var;  // Actualiza el último comando recibido
      
      switch (var) {
        case 'b':
        while (left > left_end or right < right_end) {
          left -= 5;
          right += 5;
          servo1.write(left);
          servo2.write(right);
          delay(tiempo);
        }
        // Valores finales:
        // servo1.write(30);
        // servo2.write(56);
        break;
        
      case 'a':
        while (left < left_start or right > right_start) {
          left += 5;
          right -= 5;
          servo1.write(left);
          servo2.write(right);
          delay(tiempo);
        }
        // Valores finales:
        // servo1.write(56);
        // servo2.write(34);
        break;
        
      case 'd':
        while (left > left_end or right != 45) {
          if (right < 45) {
            right += 5;
          } else {
            right -= 5;
          }
          left -= 5;
          servo1.write(left);
          servo2.write(right);
          delay(tiempo);
        }
        // Valores finales:
        // servo1.write(30);
        // servo2.write(45);
        break;
        
      case 'c':
        while (left != 45 or right < right_end) {
          if (left < 45) {
            left += 5;
          } else {
            left -= 5;
          }
          right += 5;
          servo1.write(left);
          servo2.write(right);
          delay(tiempo);
        }
        // Valores finales:
        // servo1.write(45);
        // servo2.write(56);
        break;
        
      case 'e':
        while (left != 45 or left != 45) {
            if (left < 45) {
              left += 5;
            } else {
              left -= 5;
            }
            if (right < 45) {
              right += 5;
            } else {
              right -= 5;
            }
          servo1.write(left);
          servo2.write(right);
          delay(tiempo);
        }
        // Valores finales:
        // servo1.write(45);
        // servo2.write(45);
        break;
      }
    }
  }
}
