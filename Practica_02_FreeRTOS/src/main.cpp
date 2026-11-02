
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

// =====================================
// PRACTICA 02 - FREERTOS
// ESP-32S V1.1
// Version final: Etapa 3
// =====================================

// Definicion de pines
const int LED1 = 2;
const int LED2 = 4;

// Cola de comunicacion entre tareas
QueueHandle_t cola;

// =====================================
// TAREA 1: LED integrado - Nucleo 0
// =====================================
void tareaLed1(void *pv) {

    pinMode(LED1, OUTPUT);
    bool estado = false;

    Serial.printf(
        "LED 1 ejecutandose en nucleo: %d\n",
        xPortGetCoreID()
    );

    for (;;) {
        estado = !estado;
        digitalWrite(LED1, estado);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// =====================================
// TAREA 2: LED externo - Nucleo 1
// =====================================
void tareaLed2(void *pv) {

    pinMode(LED2, OUTPUT);
    bool estado = false;

    Serial.printf(
        "LED 2 ejecutandose en nucleo: %d\n",
        xPortGetCoreID()
    );

    for (;;) {
        estado = !estado;
        digitalWrite(LED2, estado);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// =====================================
// TAREA 3: PRODUCTOR
// =====================================
void productor(void *pv) {

    int contador = 0;

    for (;;) {

        // Enviar numero a la cola
        xQueueSend(
            cola,
            &contador,
            portMAX_DELAY
        );

        // Incrementar contador
        contador++;

        // Esperar un segundo
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// =====================================
// TAREA 4: CONSUMIDOR
// =====================================
void consumidor(void *pv) {

    int dato;

    for (;;) {

        // Esperar un dato de la cola
        if (xQueueReceive(
                cola,
                &dato,
                portMAX_DELAY
            ) == pdTRUE) {

            Serial.printf(
                "Recibido: %d\n",
                dato
            );
        }
    }
}

// =====================================
// CONFIGURACION INICIAL
// =====================================
void setup() {

    // Iniciar comunicacion serial
    Serial.begin(115200);
    delay(500);

    Serial.println("");
    Serial.println("=== PRACTICA 02 FREERTOS ===");

    // Crear cola con capacidad para
    // cinco numeros enteros
    cola = xQueueCreate(5, sizeof(int));

    // Verificar creacion de la cola
    if (cola == NULL) {
        Serial.println(
            "ERROR: No se pudo crear la cola"
        );
        return;
    }

    // LED 1 asignado al nucleo 0
    xTaskCreatePinnedToCore(
        tareaLed1,
        "Led1",
        2048,
        NULL,
        1,
        NULL,
        0
    );

    // LED 2 asignado al nucleo 1
    xTaskCreatePinnedToCore(
        tareaLed2,
        "Led2",
        2048,
        NULL,
        1,
        NULL,
        1
    );

    // Tarea productora
    xTaskCreate(
        productor,
        "Prod",
        2048,
        NULL,
        1,
        NULL
    );

    // Tarea consumidora
    xTaskCreate(
        consumidor,
        "Cons",
        2048,
        NULL,
        1,
        NULL
    );
}

// =====================================
// LOOP PRINCIPAL
// =====================================
void loop() {
}
