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
} SensorData_t;
// Queue handle dùng chung
extern QueueHandle_t xSensorQueue;
extern QueueHandle_t xLCDQueue;
extern QueueHandle_t xNeoQueue;
extern SensorData_t sensorData;
extern float glob_temperature;
extern float glob_humidity;

extern String WIFI_SSID;
extern String WIFI_PASS;
extern String CORE_IOT_TOKEN;
extern String CORE_IOT_SERVER;
extern String CORE_IOT_PORT;

extern boolean isWifiConnected;
extern SemaphoreHandle_t xBinarySemaphoreInternet;
#endif