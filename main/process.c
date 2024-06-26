/**
 * @file    process.c
 * @brief   Implementation of processing functions for the project.
 *
 * @date    June, 2024
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "process.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
QueueHandle_t sensorDataQueue;
RTC_DATA_ATTR uint8_t counter_sleep = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Initialize the sensor data queue.
 */
void init_queue(void)
{
   sensorDataQueue = xQueueCreate(10, sizeof(SensorData));

   if (sensorDataQueue == NULL)
   {
      printf("\nError!\n");
   }
}

/**
 * @brief Task to manage deep sleep functionality.
 * @param parameter Pointer to the parameters passed to the task.
 */
void deep_sleep_task(void * parameter)
{

    vTaskDelay(pdMS_TO_TICKS(10000));
    // Cấu hình GPIO 32 là RTC GPIO
    rtc_gpio_init(GPIO_NUM_32);
    
    // Đặt GPIO 32 ở chế độ đầu ra và giá trị mong muốn (ví dụ: mức cao)
    rtc_gpio_set_direction(GPIO_NUM_32, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(GPIO_NUM_32, 1); // Đặt mức cao cho GPIO 32
    
    // Giữ chân GPIO 32
    esp_err_t err = rtc_gpio_hold_en(GPIO_NUM_32);
    if (err != ESP_OK) {
        ESP_LOGE(__func__, "Failed to hold GPIO 32: %s", esp_err_to_name(err));
        return;
    }

    const int wakeup_time_sec = 5 * 1000; // Thời gian tính bằng milliseconds
    ESP_LOGI(__func__, "counter_sleep: %d \n", counter_sleep);
    ESP_LOGI(__func__, "Enabling timer wakeup, %d ms\n", wakeup_time_sec);
    
    esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000); // Chuyển thành microseconds
    vTaskDelay(pdMS_TO_TICKS(5000));
    
    counter_sleep++;
    ESP_LOGI(__func__, "Entering deep sleep\n");
    esp_deep_sleep_start();
}

/**
 * @brief Initialize the application.
 */
void app_init(void)
{
    // Init NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    init_wifi(); // Initialize and connect to Wi-Fi
    init_mqtt(); // Start the MQTT client

    init_queue();
    init_ili9341();
    init_sensors();
}

/**
 * @brief Main application task.
 */
void app_task(void)
{
    xTaskCreate(sensor_task, "sensor_task", 2048 * 5, NULL, 10U, NULL);
    xTaskCreate(mqtt_task, "mqtt_task", configMINIMAL_STACK_SIZE * 3, NULL, 5U, NULL);
    xTaskCreate(display_task, "display_task", configMINIMAL_STACK_SIZE * 3, NULL, 7U, NULL);
    xTaskCreate(deep_sleep_task,"Deepsleep", (1024 * 16), NULL, (UBaseType_t) 2, NULL);
}
