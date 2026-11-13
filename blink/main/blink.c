/*

FUNCTION: blinks the LED on GPIO 13 every 250 ms

*/
#include <stdio.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DEFAULT_LED_PIN 13   
#define PERIOD_MS 250

typedef struct {
    bool led_on;
} self_t;

static void startup(self_t *self) {
    gpio_reset_pin(DEFAULT_LED_PIN);
    gpio_set_direction(DEFAULT_LED_PIN, GPIO_MODE_OUTPUT);
}

static void on_timer(self_t *self) {
    self->led_on = !self->led_on;
    printf("LED State: %d\n", self->led_on);
    gpio_set_level(DEFAULT_LED_PIN, self->led_on);
}

static void blink(void *arg) {
    static self_t self = { .led_on = false };
    startup(&self);
    TickType_t last = xTaskGetTickCount();
    while (1) {
        on_timer(&self);
        vTaskDelayUntil(&last, pdMS_TO_TICKS(PERIOD_MS));
    } 
}

void app_main(void) {
    xTaskCreate(blink, "blink", 2048, NULL, 5, NULL);
}
