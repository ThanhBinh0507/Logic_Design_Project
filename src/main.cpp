#include "global.h"

#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_humi_monitor.h"
// #include "mainserver.h"
// #include "tinyml.h"
#include "coreiot.h"
#include "lcd.h"

// include task
#include "task_check_info.h"
#include "task_toogle_boot.h"
#include "task_wifi.h"
#include "task_webserver.h"
#include "task_core_iot.h"

void setup()
{
  Serial.begin(115200);
  xNeoQueue = xQueueCreate(1, sizeof(SensorData_t));
  xLCDQueue = xQueueCreate(1, sizeof(SensorData_t));
  // Tạo queue chứa 1 phần tử kiểu SensorData_t
  xSensorQueue = xQueueCreate(1, sizeof(SensorData_t));
  if (xSensorQueue == NULL || xLCDQueue == NULL) {
    Serial.println("Failed to create queue!");
    while(1);
  }
  check_info_File(0);

  // Khởi tạo task
  xTaskCreate(led_blinky, "Task LED Blink", 4096, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task NEO Blink", 2048, NULL, 2, NULL);
  xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 4096, NULL, 2, NULL);
  xTaskCreate(lcd_display, "Task LCD", 4096, NULL, 2, NULL);
  // xTaskCreate(main_server_task, "Task Main Server" ,8192  ,NULL  ,2 , NULL);
  // xTaskCreate( tiny_ml_task, "Tiny ML Task" ,2048  ,NULL  ,2 , NULL);
  // xTaskCreate(coreiot_task, "CoreIOT Task" ,4096  ,NULL  ,2 , NULL);
  // xTaskCreate(Task_Toogle_BOOT, "Task_Toogle_BOOT", 4096, NULL, 2, NULL);

   Serial.println("All tasks started!");
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
//   if (check_info_File(1))
//   {
//     if (!Wifi_reconnect())
//     {
//       Webserver_stop();
//     }
//     else
//     {
//       //CORE_IOT_reconnect();
//     }
//   }
//   Webserver_reconnect();
// }