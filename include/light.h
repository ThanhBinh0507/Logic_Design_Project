#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "global.h"
// Chân kết nối LDR
<<<<<<< HEAD
#define LIGHT_PIN 16  // dùng chân ADC1_CH1 trên Yolo UNO
=======
#define LIGHT_PIN 12  // dùng chân ADC1_CH1 trên Yolo UNO
>>>>>>> b76eaa43f33bd6f91a042d7e94ebfad5090ca475


// Queue chứa trạng thái ánh sáng (true = sáng, false = tối)
extern QueueHandle_t xLightQueue;

// Hàm task cảm biến ánh sáng
void Light_Task(void *pvParameters);

// Khởi tạo cảm biến

#endif
