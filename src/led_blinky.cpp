#include "led_blinky.h"

void led_blinky(void *pvParameters){
  pinMode(LED_GPIO, OUTPUT);
  
  uint32_t blinkDelay = 500; // mặc định
  SensorData_t receivedData;
  float temp = 0;
  float humi = 0;

  while (1) {
    // Chờ dữ liệu mới từ queue
    if (xQueueReceive(xSensorQueue, &receivedData, 0) == pdTRUE) {
      temp = receivedData.temperature;
      humi = receivedData.humidity;

      if (temp < 20 || temp > 35) blinkDelay = 100;
     else if ( (temp >= 20 && temp < 25) || (temp > 30 && temp <= 35) )
      blinkDelay = 500;
      else blinkDelay = 2000;

      Serial.printf("Temperature = %.2f°C | Humidity = %.2f%% => LED blink = %lu ms\n",
                    temp, humi, blinkDelay);
    }

    // LED nháy liên tục với tốc độ hiện tại
    digitalWrite(LED_GPIO, !digitalRead(LED_GPIO));
    vTaskDelay(pdMS_TO_TICKS(blinkDelay));
  }
}