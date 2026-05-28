#ifndef DOOR_H
#define DOOR_H

#include <ESP32Servo.h>

// Định nghĩa chân servo
#define DOOR_SERVO_PIN 38 // ⭐ Thay đổi theo chân thực tế của bạn

// Khai báo đối tượng servo (extern để dùng trong .cpp)
extern Servo doorServo;

// Khai báo các hàm
void DOOR_Init();
void DOOR_Open();
void DOOR_Close();
void Door_Task(void *pvParameters);

#endif