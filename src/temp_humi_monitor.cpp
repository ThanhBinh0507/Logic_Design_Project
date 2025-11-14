#include "temp_humi_monitor.h"
DHT20 dht20;
LiquidCrystal_I2C lcd(33,16,2);

void temp_humi_monitor(void *pvParameters){
    Wire.begin(11, 12);
    dht20.begin();

    while (1) {
        dht20.read();
        sensorData.temperature = dht20.getTemperature();
        sensorData.humidity = dht20.getHumidity();

        // Serial.printf("Humidity: %.2f%%  Temperature: %.2f°C\n", sensorData.humidity, sensorData.temperature);

        // Gửi dữ liệu vào Queue
        xQueueOverwrite(xSensorQueue, &sensorData);
        xQueueOverwrite(xLCDQueue, &sensorData);
        xQueueOverwrite(xNeoQueue, &sensorData);

        vTaskDelay(pdMS_TO_TICKS(5000)); // đọc mỗi 5s
    }
}
