
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

const int LED1 = 2;
const int LED2 = 4;

SemaphoreHandle_t turnoLed1;
SemaphoreHandle_t turnoLed2;

// Tarea 1: nucleo 0
void tareaLed1(void *pv) {
    pinMode(LED1, OUTPUT);
    bool estado = false;

    for (;;) {
        xSemaphoreTake(turnoLed1, portMAX_DELAY);

        estado = !estado;
        digitalWrite(LED1, estado);

        Serial.printf("LED 1 ejecutandose en nucleo: %d\n",
                      xPortGetCoreID());

        xSemaphoreGive(turnoLed2);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Tarea 2: nucleo 1
void tareaLed2(void *pv) {
    pinMode(LED2, OUTPUT);
    bool estado = false;

    for (;;) {
        xSemaphoreTake(turnoLed2, portMAX_DELAY);

        estado = !estado;
        digitalWrite(LED2, estado);

        Serial.printf("LED 2 ejecutandose en nucleo: %d\n",
                      xPortGetCoreID());

        xSemaphoreGive(turnoLed1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup() {
    Serial.begin(115200);
    delay(500);

    turnoLed1 = xSemaphoreCreateBinary();
    turnoLed2 = xSemaphoreCreateBinary();

    if (turnoLed1 == NULL || turnoLed2 == NULL) {
        Serial.println("Error al crear semaforos");
        return;
    }

    xTaskCreatePinnedToCore(
        tareaLed1, "Led1", 2048, NULL, 1, NULL, 0
    );

    xTaskCreatePinnedToCore(
        tareaLed2, "Led2", 2048, NULL, 1, NULL, 1
    );

    xSemaphoreGive(turnoLed1);
}

void loop() {
}
