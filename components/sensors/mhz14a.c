/**
 * @file    mhz14a.c
 * @brief   Implementation of functions for interacting with the MH-Z14A sensor.
 *
 * @date    June, 2024
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "mhz14a.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/**
 * @brief Initialize UART for MH-Z14A sensor.
 */
void init_uart_mhz14a(void)
{
    const uart_config_t uart_config = {
        .baud_rate = UART_MHZ14A_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_MHZ14A_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_MHZ14A_NUM, &uart_config);
    uart_set_pin(UART_MHZ14A_NUM, UART_MHZ14A_TXD_PIN, UART_MHZ14A_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

/**
 * @brief Transmit data via UART to MH-Z14A sensor.
 *
 * @param logName Name of the log.
 * @param uart_num UART port number.
 * @param data Data to be transmitted.
 * @param len Length of the data.
 *
 * @return Number of bytes transmitted.
 */
int transmit_uart_mhz14a(const char* logName, uart_port_t uart_num, const char* data, const int len)
{
    const int txBytes = uart_write_bytes(uart_num, data, len);
    // ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

/**
 * @brief Task to handle receiving data from MH-Z14A sensor.
 *
 * @param arg Pointer to task arguments (unused).
 */
void rx_mhz14a_task(void *arg)
{
    static const char *TX_TASK_TAG = "TX_MHZ14A_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    const char mhz14a_query_co2_cmd[] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };
    const int cmd_len = sizeof(mhz14a_query_co2_cmd);

    static const char *RX_TASK_TAG = "RX_MHZ14A_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE + 1);
    while (1) {
        transmit_uart_mhz14a(TX_TASK_TAG, UART_MHZ14A_NUM, mhz14a_query_co2_cmd, cmd_len);

        const int rxBytes = uart_read_bytes(UART_MHZ14A_NUM, data, RX_BUF_SIZE, 1000 / portTICK_PERIOD_MS);
        if (rxBytes > 0)
        {
            data[rxBytes] = 0;
            // ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            // ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);

            uint16_t raw_co2 = data[2] * 0x100 + data[3];
            sensorData.CO2 = calibrate_co2((float)raw_co2);

            if (sensorData.CO2 >= 1000)
            {
                sensorData.CO2 /= 2;
            }

            ESP_LOGI(RX_TASK_TAG, "Calibrated CO2 Concentration: %.2f ppm\n\n", sensorData.CO2);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
    free(data);
}