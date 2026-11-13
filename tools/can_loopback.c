#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/twai.h"
#include "esp_log.h"

// need to place in /main/main.c for ESP-IDF can run it, but overall working code below

void app_main(void)
{
    twai_general_config_t g = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_25, GPIO_NUM_26, TWAI_MODE_NO_ACK);
    twai_timing_config_t t = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    twai_driver_install(&g, &t, &f);
    twai_start();

    uint8_t count = 0;
    while (1)
    {
        twai_message_t tx = {0};
        tx.identifier = 0x100;
        tx.data_length_code = 1;
        tx.data[0] = count;
        tx.self = 1;
        twai_transmit(&tx, pdMS_TO_TICKS(100));

        twai_message_t rx;
        if (twai_receive(&rx, pdMS_TO_TICKS(500)) == ESP_OK)
            ESP_LOGI("CAN", "PASS: got %u", rx.data[0]);
        else
            ESP_LOGW("CAN", "FAIL");

        count++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}