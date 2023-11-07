
// Created by acer-zgy on 2023/11/7.
//
#include "FreeRTOS.h"
#include "task.h"
#include "firstTask.h"
#include "led.h"


_Noreturn void Led_task(void *argument) {
    Led_init();


    while (1) {
        vTaskDelay(200);
        led_turn();
    }
};

