/**
 * @file    pms7003.c
 * @brief   Implementation of functions for interacting with the PMS7003 sensor.
 *
 * @date    June, 2024
 */

#include "pms7003.h"

/*******************************************************************************
 * Constants and Macros
 ******************************************************************************/
const char *TAG_PMS7003 = "PMS7003"; ///< Tag for logging.

/*******************************************************************************
 * Calibration Functions
 ******************************************************************************/

/**
 * @brief Calibrate PM1.0 sensor data.
 * @param raw_pm1_0 Raw PM1.0 data.
 * @return Calibrated PM1.0 data.
 */
float calibrate_pm1_0(float raw_pm1_0) { return raw_pm1_0 + 5.0; }

/**
 * @brief Calibrate PM2.5 sensor data.
 * @param raw_pm2_5 Raw PM2.5 data.
 * @return Calibrated PM2.5 data.
 */
float calibrate_pm2_5(float raw_pm2_5) { return raw_pm2_5 + 3.0; }

/**
 * @brief Calibrate PM10 sensor data.
 * @param raw_pm10 Raw PM10 data.
 * @return Calibrated PM10 data.
 */
float calibrate_pm10(float raw_pm10) { return raw_pm10 + 2.0; }

/**
 * @brief Calibrate CO2 sensor data.
 * @param raw_co2 Raw CO2 data.
 * @return Calibrated CO2 data.
 */
float calibrate_co2(float raw_co2) { return raw_co2 * 1.1; }

/**
 * @brief Calibrate temperature sensor data.
 * @param raw_temp Raw temperature data.
 * @return Calibrated temperature data.
 */
float calibrate_temperature(float raw_temp) { return raw_temp + 0.5; }

/**
 * @brief Calibrate humidity sensor data.
 * @param raw_hum Raw humidity data.
 * @return Calibrated humidity data.
 */
float calibrate_humidity(float raw_hum) { return raw_hum + 2.0; }

/*******************************************************************************
 * Function Definitions
 ******************************************************************************/

/**
 * @brief Read data from PMS7003 sensor.
 * @param pm1_0 Pointer to store PM1.0 data.
 * @param pm2_5 Pointer to store PM2.5 data.
 * @param pm10 Pointer to store PM10 data.
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t pms7003_readData(uint32_t *pm1_0, uint32_t *pm2_5, uint32_t *pm10)
{
    vTaskDelay(2000 / portTICK_PERIOD_MS);  // Wait for 2 seconds
    uint8_t rawData[RX_BUFFER_SIZE];
    int lengthSensorDataArray = uart_read_bytes(UART_PMS7003_NUM, rawData, RX_BUFFER_SIZE, 100 / portTICK_PERIOD_MS);

    bool check = false;
    for (int i = 0; i < lengthSensorDataArray - 6; i++)
    {
        if (rawData[i] == 0x42 && rawData[i + 1] == 0x4d) // Check header packet
        {
            int startByte = i + 4; // Skip 4 first bytes of header and frame length

            *pm1_0 = ((uint32_t)rawData[startByte] << 8) + rawData[startByte + 1];
            *pm2_5 = ((uint32_t)rawData[startByte + 2] << 8) + rawData[startByte + 3];
            *pm10  = ((uint32_t)rawData[startByte + 4] << 8) + rawData[startByte + 5];

            ESP_LOGI(TAG_PMS7003, "PMS7003 sensor read data successful.");
            ESP_LOGI(TAG_PMS7003, "PM1.0: %" PRIu32 " ug/m3, PM2.5: %" PRIu32 " ug/m3, PM10: %" PRIu32 " ug/m3", *pm1_0, *pm2_5, *pm10);
            check = true;
            break;
        }
    }

    if (!check)
    {
        ESP_LOGE(TAG_PMS7003, "PMS7003 sensor read data failed.");
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief Initialize UART for PMS7003 sensor.
 */
void init_uart_pms7003(void)
{
    const uart_config_t uart_config = {
        .baud_rate = UART_PMS7003_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_PMS7003_NUM, 1024 * 2, 0, 0, NULL, 0);
    uart_param_config(UART_PMS7003_NUM, &uart_config);
    uart_set_pin(UART_PMS7003_NUM, UART_PMS7003_TXD_PIN, UART_PMS7003_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); 
}

/**
 * @brief Task to handle receiving data from PMS7003 sensor.
 * @param arg Pointer to task arguments (unused).
 */
void rx_pms7003_task(void *arg)
{
    uint32_t pm1_0, pm2_5, pm10;
    while (1)
    {
        esp_err_t err = pms7003_readData(&pm1_0, &pm2_5, &pm10);
        if (err == ESP_OK) {
            // Apply calibration to sensor data
            sensorData.pm1_0 = (float)pm1_0;
            sensorData.pm2_5 = (float)pm2_5;
            sensorData.pm10 = (float)pm10;
            ESP_LOGI(TAG_PMS7003, "Calibrated PM1.0: %.2f ug/m3, PM2.5: %.2f ug/m3, PM10: %.2f ug/m3", sensorData.pm1_0, sensorData.pm2_5, sensorData.pm10);
        }
        else
        {
            ESP_LOGE(TAG_PMS7003, "Failed to read data from PMS7003");
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay for 2 seconds
    }
}