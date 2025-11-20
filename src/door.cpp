#include "door.h"

// ========== Cấu hình servo ==========
static const int DOOR_PIN = 5;        // đổi theo chân bạn muốn
static const int DOOR_CHANNEL = 0;
static const int DOOR_TIMER = 0;

static const int DOOR_PWM_FREQ = 50;         // servo: 50Hz
static const int DOOR_PWM_RES  = 16;         // 16-bit PWM

static const float MIN_PULSE_MS = 0.5f;
static const float MAX_PULSE_MS = 2.4f;
static const float PERIOD_MS    = 1000.0f / DOOR_PWM_FREQ;

// ========== Hàm chuyển góc → duty ==========
static uint32_t angleToDuty(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    float pulse = MIN_PULSE_MS + (angle / 180.0f) * (MAX_PULSE_MS - MIN_PULSE_MS);
    float dutyFraction = pulse / PERIOD_MS;
    uint32_t maxDuty = (1UL << DOOR_PWM_RES) - 1;

    return (uint32_t)(dutyFraction * maxDuty);
}

// ========== Task cửa xoay vòng ==========
void doorTask(void *pvParameters) {
    ledcSetup(DOOR_TIMER, DOOR_PWM_FREQ, DOOR_PWM_RES);
    ledcAttachPin(DOOR_PIN, DOOR_CHANNEL);

    int angle = 0;
    int direction = 1;  // 1 = tăng, -1 = giảm

    while (1) {
        // Viết duty
        ledcWrite(DOOR_CHANNEL, angleToDuty(angle));

        // Tăng / giảm góc
        angle += direction;

        // Đổi chiều khi chạm biên
        if (angle >= 180) {
            angle = 180;
            direction = -1;
            vTaskDelay(pdMS_TO_TICKS(300)); // dừng 0.3s ở biên
        } else if (angle <= 0) {
            angle = 0;
            direction = 1;
            vTaskDelay(pdMS_TO_TICKS(300));
        }

        // Delay để servo di chuyển mượt
        vTaskDelay(pdMS_TO_TICKS(15));
    }
}
