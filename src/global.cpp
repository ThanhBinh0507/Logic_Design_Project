#include "global.h"
float glob_temperature = 0;
float glob_humidity = 0;

String WIFI_SSID;
String WIFI_PASS;
String CORE_IOT_TOKEN;
String CORE_IOT_SERVER;
String CORE_IOT_PORT;

String ssid = "ESP32-YOUR NETWORK HERE!!!";
String password = "12345678";
String wifi_ssid = "abcde";
String wifi_password = "123456789";
boolean isWifiConnected = false;
SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();
QueueHandle_t xSensorQueue = NULL;
QueueHandle_t xLCDQueue = NULL;
QueueHandle_t xNeoQueue = NULL;
QueueHandle_t xServerQueue = NULL;
<<<<<<< HEAD
QueueHandle_t xTinyMLQueue = NULL;
SemaphoreHandle_t xLCDSemaphore = NULL;

=======
SemaphoreHandle_t xLCDSemaphore = NULL;
>>>>>>> b76eaa43f33bd6f91a042d7e94ebfad5090ca475
SensorData_t sensorData = {0};