#include "door.h"
#include <Arduino.h>
#include "global.h" // Chứa SensorData_t và xDoorQueue
#include "temp_humi_monitor.h"

// Định nghĩa đối tượng Servo được khai báo trong door.h
Servo doorServo;


// Góc mở và đóng của servo (micro servo 9g thường có 0-180 độ)
#define OPEN_ANGLE 90
#define CLOSE_ANGLE 0
#define IDLE_DELAY_MS 500 // Thời gian chờ mặc định


/**
 * @brief Khởi tạo hệ thống điều khiển cửa (Servo).
 * CHỈ GỌI MỘT LẦN TRONG setup().
 */
void DOOR_Init() {


    // 2. Gắn đối tượng servo vào chân (CHỈ GỌI MỘT LẦN!)
    // Sử dụng giới hạn xung (500us min, 2500us max)
    doorServo.attach(DOOR_SERVO_PIN, 544, 2400);
    // 3. Đảm bảo cửa đóng ngay khi khởi động
    doorServo.write(CLOSE_ANGLE);
    Serial.println("DOOR_Init(): Servo attached and set to CLOSE (0)."); // DEBUG
}


/**
 * @brief Mở cửa bằng cách di chuyển servo đến góc mở.
 */
void DOOR_Open() {
    doorServo.write(CLOSE_ANGLE);
    Serial.println("DOOR_Open() called."); // DEBUG
}


/**
 * @brief Đóng cửa bằng cách di chuyển servo đến góc đóng.
 */
void DOOR_Close() {
    doorServo.write(OPEN_ANGLE);
    Serial.println("DOOR_Close() called."); // DEBUG
}


/**
 * @brief Task Cửa điều khiển theo điều kiện nhiệt độ/độ ẩm.
 */
void Door_Task(void *pvParameters) {
    Serial.println("Door_Task START");
   
    SensorData_t receivedData;
    float humi = 0;
    bool is_open = false;
   
    DOOR_Close();
    vTaskDelay(pdMS_TO_TICKS(1000));


    while (1) {
       
        if (xQueueReceive(xDoorQueue, &receivedData, 0) == pdTRUE) {
            humi = receivedData.humidity;
        }


        bool should_open = (humi >= 60 && humi <= 80);


        if (should_open && !is_open) {
            DOOR_Open();
            is_open = true;
            vTaskDelay(pdMS_TO_TICKS(500)); // ⭐ Giảm từ 800→500ms
        }
        else if (!should_open && is_open) {
            DOOR_Close();
            is_open = false;
            vTaskDelay(pdMS_TO_TICKS(500)); // ⭐ Giảm từ 800→500ms
        }
       
        vTaskDelay(pdMS_TO_TICKS(200)); // ⭐ Giảm từ 1000→200ms (kiểm tra 5 lần/giây)
    }
}

