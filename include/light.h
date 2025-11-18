#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "global.h"
// Chân kết nối LDR
#define LIGHT_PIN 4  // dùng chân ADC1_CH1 trên Yolo UNO


// Queue chứa trạng thái ánh sáng (true = sáng, false = tối)
extern QueueHandle_t xLightQueue;

// Hàm task cảm biến ánh sáng
void Light_Task(void *pvParameters);

// Khởi tạo cảm biến

#endif
