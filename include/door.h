#pragma once
#include <Arduino.h>

void doorTask(void *pvParameters);

// Hàm điều khiển góc cửa từ task khác (nếu muốn)
void doorSetAngle(int angle);
