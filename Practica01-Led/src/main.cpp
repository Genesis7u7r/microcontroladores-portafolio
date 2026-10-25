
#include <Arduino.h>

// Declarar el pin GPIO4 para el LED externo
const int LED = 4;

void setup() {
    // Configurar el GPIO4 como salida
    pinMode(LED, OUTPUT);
}

void loop() {
    // Encender el LED durante 500 milisegundos
    digitalWrite(LED, HIGH);
    delay(500);

    // Apagar el LED durante 500 milisegundos
    digitalWrite(LED, LOW);
    delay(500);
}
