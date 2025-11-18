#include "lcd.h"
#include "global.h"
#include <LiquidCrystal_I2C.h>

void lcd_display(void *pvParameters) {
  lcd.begin();
  lcd.backlight();
  lcd.clear();

SensorData_t receivedData; // Tạo một biến cục bộ để chứa dữ liệu
float temp = 0;
float humi = 0;

  while (1) {
    // Chờ dữ liệu mới
    if (xQueueReceive(xLCDQueue, &receivedData, 0) == pdTRUE) {

      temp = receivedData.temperature;
      humi = receivedData.humidity;

      lcd.setCursor(0, 0);
      {
        char buf[32];
        snprintf(buf, sizeof(buf), "T:%.1fC H:%.1f%%", temp, humi);
        lcd.print(buf);
      }

      // Xác định trạng thái
     // Xác định trạng thái
     String state;
      lcd.setCursor(0, 1); // Đặt con trỏ cho dòng 2

      // 1. TRƯỜNG HỢP CRITICAL (Ưu tiên cao nhất)
      // Yêu cầu: Temp < 20 OR Temp > 35 OR Humi < 50 OR Humi > 90
      if ( (temp < 20 || temp > 35) || (humi < 50 || humi > 90) )
      {
        state = "CRITICAL";
        lcd.print("Status: CRIT! "); // Chuỗi 16 ký tự
      }
      
      // 2. TRƯỜNG HỢP WARNING (Nếu không Critical, mới xét tới Warning)
      // Yêu cầu: Temp [20, 25) OR (30, 35] OR Humi [50, 60) OR (80, 90]
      else if ( (temp >= 20 && temp < 25) || (temp > 30 && temp <= 35) || 
                (humi >= 50 && humi < 60) || (humi > 80 && humi <= 90) )
      {
        state = "WARNING";
        lcd.print("Status: WARN  "); // Chuỗi 16 ký tự
      }
      
      // 3. TRƯỜNG HỢP NORMAL (Trường hợp còn lại)
      // Tức là: Temp [25, 30] AND Humi [60, 80]
      else
      {
        state = "NORMAL";
        lcd.print("Status: NORMAL "); // Chuỗi 16 ký tự
      }
      // In ra Serial để debug
      Serial.printf("[LCD] %s Mode - %.1f°C, %.1f%%\n", state.c_str(), temp, humi);
    }
     vTaskDelay(pdMS_TO_TICKS(250));
  }
}