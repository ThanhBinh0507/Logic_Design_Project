#include <Arduino.h>

#define FAN_PIN 10     // đổi theo chân bạn dùng
#define FAN_PERIOD 500   // 500ms = 0.5s

void fanTask(void *pvParameters) {
    pinMode(FAN_PIN, OUTPUT);

    while (1) {
        digitalWrite(FAN_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(FAN_PERIOD));

        digitalWrite(FAN_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(FAN_PERIOD));
    }
}
