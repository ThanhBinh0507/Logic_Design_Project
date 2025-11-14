#include "neo_blinky.h"
#include "temp_humi_monitor.h"

void neo_blinky(void *pvParameters){

    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    SensorData_t receivedData;
    SensorData_t latestData = {0};

    while(1) {                          
        if (xQueueReceive(xNeoQueue, &receivedData, pdMS_TO_TICKS(10)) == pdPASS) {
            latestData = receivedData; // cập nhật dữ liệu mới
        }

        float humi = latestData.humidity;

        // Xác định màu LED theo độ ẩm
        uint32_t color;
        if (humi < 50 || humi > 90){
            color = strip.Color(255, 0, 0); // đỏ
        } 
        else if ( (humi >= 50 && humi < 60) || (humi > 80 && humi <= 90) ) {
            color = strip.Color(255, 255, 0);   // vàng
        } 
        else {
            color = strip.Color(255, 255, 255); // trắng
        }

        // Nháy LED 0.5s/lần (on 0.25s + off 0.25s)
        strip.setPixelColor(0, color);
        strip.show();
        vTaskDelay(pdMS_TO_TICKS(250));

        strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
        strip.show();
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}