
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Definicion de pines
const int LED1 = 2;
const int LED2 = 4;

// Tarea 1: LED integrado, nucleo 0
void tareaLED1(void *parameter) {
  for (;;) {
    Serial.print("LED 1 ejecutandose en nucleo: ");
    Serial.println(xPortGetCoreID());

    digitalWrite(LED1, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));

    digitalWrite(LED1, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Tarea 2: LED externo, nucleo 1
void tareaLED2(void *parameter) {
  for (;;) {
    Serial.print("LED 2 ejecutandose en nucleo: ");
    Serial.println(xPortGetCoreID());

    digitalWrite(LED2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));

    digitalWrite(LED2, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Crear tarea LED1 en nucleo 0
  xTaskCreatePinnedToCore(
    tareaLED1,
    "Tarea LED 1",
    2048,
    NULL,
    1,
    NULL,
    0
  );

  // Crear tarea LED2 en nucleo 1
  xTaskCreatePinnedToCore(
    tareaLED2,
    "Tarea LED 2",
    2048,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
  // Las tareas se ejecutan mediante FreeRTOS
}
