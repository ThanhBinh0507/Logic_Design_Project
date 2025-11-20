#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Cấu trúc dữ liệu gói tin gửi qua Queue
typedef struct {
  float temperature;
  float humidity;
<<<<<<< HEAD
  float label;
=======
  int label;
>>>>>>> b76eaa43f33bd6f91a042d7e94ebfad5090ca475
} SensorData_t;
// Queue handle dùng chung
extern QueueHandle_t xSensorQueue;
extern QueueHandle_t xLCDQueue;
extern QueueHandle_t xNeoQueue;
extern SensorData_t sensorData;
<<<<<<< HEAD
extern QueueHandle_t xServerQueue;
extern QueueHandle_t xTinyMLQueue;
extern float glob_temperature;
extern float glob_humidity;
// Các biến cờ trạng thái LED (đã được bạn sử dụng trong handleToggle)
extern bool led1_state; // Dành cho led_blinky (LED thường)
extern bool led2_state; // Dành cho neo_blinky (NeoPixel)
=======
extern float glob_temperature;
extern float glob_humidity;
>>>>>>> b76eaa43f33bd6f91a042d7e94ebfad5090ca475

extern String WIFI_SSID;
extern String WIFI_PASS;
extern String CORE_IOT_TOKEN;
extern String CORE_IOT_SERVER;
extern String CORE_IOT_PORT;
<<<<<<< HEAD
extern String ssid;
extern String password;

extern String wifi_ssid;
extern String wifi_password;
=======
>>>>>>> b76eaa43f33bd6f91a042d7e94ebfad5090ca475

extern boolean isWifiConnected;
extern SemaphoreHandle_t xBinarySemaphoreInternet;
#endif