/*
 * @Author: your name
 * @Date: 2022-03-11 09:15:40
 * @LastEditTime: 2022-03-11 14:14:46
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \9.ESP-IDF实验\esp.ino
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void setup(void)
{
    gpio_pad_select_gpio(GPIO_NUM_4);
    // gpio_init();
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
}
void loop()
{
    /* Blink off (output low) */
    printf("Turning off the LED\n");
    gpio_set_level(GPIO_NUM_4, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    /* Blink on (output high) */
    printf("Turning on the LED\n");
    gpio_set_level(GPIO_NUM_4, 0);
    ESP_LOGI(TAG,"Something");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
