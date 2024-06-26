/**
 * @file    sensors.c
 * @brief   Implementation of sensor handling functions.
 *
 * @date    June, 2024
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sensors.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
SensorData sensorData; ///< Global variable holding sensor data.

/*******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief Initialize sensors.
 */
void init_sensors(void)
{
    init_uart_mhz14a();    // Initialize UART for MH-Z14A sensor
    init_uart_pms7003();   // Initialize UART for PMS7003 sensor
    init_i2c_bme280();     // Initialize I2C for BME280 sensor
}

/**
 * @brief Task to handle sensor data acquisition.
 * @param arg Pointer to task arguments (unused).
 */
void sensor_task(void *arg)
{
    // Create tasks for handling sensor data reception
    xTaskCreate(rx_mhz14a_task, "uart_rx_mhz14a_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(rx_pms7003_task, "uart_rx_pms7003_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(i2c_bme280_task, "i2c_bme280_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    
    while (1)
    {
        // Send sensor data to the queue
        if (xQueueSend(sensorDataQueue, &sensorData, portMAX_DELAY) == pdPASS)
        {
            printf("\nAvailable after enqueue: %d \n\n", uxQueueSpacesAvailable(sensorDataQueue));
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay between sending sensor data
    }
}