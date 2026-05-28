#include "tinyml.h"
#include "global.h" // QUAN TRỌNG: Phải include file này
// Globals, for the convenience of one-shot setup.

//thêm tham số chuẩn hoá
const float TEMP_MEAN = 27.489335f;
const float TEMP_STD = 3.599392f;
const float HUMI_MEAN = 68.958808f;
const float HUMI_STD = 10.510962f;


float normalize(float value, float mean, float std)
{
    return (value - mean) / std;
}

namespace
{
    tflite::ErrorReporter *error_reporter = nullptr;
    const tflite::Model *model = nullptr;
    tflite::MicroInterpreter *interpreter = nullptr;
    TfLiteTensor *input = nullptr;
    TfLiteTensor *output = nullptr;
    constexpr int kTensorArenaSize = 8 * 1024; // Adjust size based on your model
    uint8_t tensor_arena[kTensorArenaSize];
} // namespace

void setupTinyML()
{
    Serial.println("TensorFlow Lite Init....");
    static tflite::MicroErrorReporter micro_error_reporter;
    error_reporter = &micro_error_reporter;

    model = tflite::GetModel(dht_anomaly_model_tflite); // g_model_data is from model_data.h
    if (model->version() != TFLITE_SCHEMA_VERSION)
    {
        error_reporter->Report("Model provided is schema version %d, not equal to supported version %d.",
                               model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }

    static tflite::AllOpsResolver resolver;
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk)
    {
        error_reporter->Report("AllocateTensors() failed");
        return;
    }

    input = interpreter->input(0);
    output = interpreter->output(0);

    Serial.println("TensorFlow Lite Micro initialized on ESP32.");
}
SensorData_t receivedData; 

void tiny_ml_task(void *pvParameters)
{

    setupTinyML();

    while (1)
    {
        if (xQueueReceive(xTinyMLQueue, &receivedData, 0) == pdTRUE){
            // Prepare input data (e.g., sensor readings)
            // For a simple example, let's assume a single float input

            //chuẩn hoá dữ liệu trước khi đưa vào model
            float temp_raw = receivedData.temperature;
            float humi_raw = receivedData.humidity;
            
            float temp_normalized = normalize(temp_raw, TEMP_MEAN, TEMP_STD);
            float humi_normalized = normalize(humi_raw, HUMI_MEAN, HUMI_STD);

            //chuẩn bị dữ liệu đầu vào
            if (input->type == kTfLiteFloat32)
            {
                input->data.f[0] = temp_normalized;
                input->data.f[1] = humi_normalized;
            }
            else if (input->type == kTfLiteInt8)
            {
                input->data.int8[0] = (int8_t)(temp_normalized / input->params.scale + input->params.zero_point);
                input->data.int8[1] = (int8_t)(humi_normalized / input->params.scale + input->params.zero_point);
            }
            else
            {
                error_reporter->Report("Unsupported input type");
                continue;
            }



            // Run inference 
            if (interpreter->Invoke() != kTfLiteOk)
            {
                error_reporter->Report("Invoke failed");
                continue;
            }

            // Get and process output
            float result = 0;
            if (output->type == kTfLiteFloat32)
            {
                result = output->data.f[0];
            }
            else if (output->type == kTfLiteInt8)
            {
                // Dequantize output
                result = (output->data.int8[0] - output->params.zero_point) * output->params.scale;
            }
            else
            {
                error_reporter->Report("Unsupported output type");
                continue;
            }

            // Hiển thị kết quả với phân loại rõ ràng
            Serial.print("Inference result: ");
            Serial.print(result, 6);
            Serial.print(" → ");
            if (result > 0.5)
            {
                Serial.println("ABNORMAL");
            }
            else
            {
                Serial.println("NORMAL");
            }
            AIResult_t outputData;
            outputData.ai_score = result;

            if (xAIResultQueue != NULL) {
                // QUAN TRỌNG: Dùng Overwrite thay vì Send
                xQueueOverwrite(xAIResultQueue, &outputData);
            }
        }
        
        //Delay nhẹ để tránh Watchdog nếu chạy quá nhanh
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
