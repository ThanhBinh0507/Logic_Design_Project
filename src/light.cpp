// #include "light.h"

// // Tạo queue global
// QueueHandle_t xLightQueue = NULL;


// void Light_Task(void *pvParameters) {
    
//     bool lightState = false;
//     const int threshold = 500;  // ngưỡng ánh sáng (0–1023)

//     while(1) {
//         int sensorValue = analogRead(LIGHT_PIN);

//         // Nếu giá trị > threshold → sáng, else tối
//         lightState = (sensorValue > threshold);

//         // Gửi trạng thái vào queue
//         if (xLightQueue != NULL) {
//             xQueueOverwrite(xLightQueue, &lightState);
//         }

//         // Debug Serial
//         Serial.printf("Light: %d -> %s\n", sensorValue, lightState ? "Bright" : "Dark");

//         vTaskDelay(pdMS_TO_TICKS(5000)); // đọc mỗi 0.5 giây
//     }
// }
