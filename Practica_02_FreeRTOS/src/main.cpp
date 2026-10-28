
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Definicion de pines
const int LED1 = 2;
const int LED2 = 4;

// Tarea 1: LED integrado
void tareaLED1(void *parameter) {
  for (;;) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));

    digitalWrite(LED1, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Tarea 2: LED externo
void tareaLED2(void *parameter) {
  for (;;) {
    digitalWrite(LED2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));

    digitalWrite(LED2, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  xTaskCreate(
    tareaLED1,
    "Tarea LED 1",
    2048,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    tareaLED2,
    "Tarea LED 2",
    2048,
    NULL,
    1,
    NULL
  );
}

void loop() {
  // Las tareas son controladas por FreeRTOS
}
