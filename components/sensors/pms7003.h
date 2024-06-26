/**
 * @file    pms7003.h
 * @brief   Header file for PMS7003 sensor module.
 *
 * @details This file contains the necessary includes, macro definitions,
 *          and function prototypes for interacting with the PMS7003 sensor.
 * 
 * @date    June, 2024
 */

#ifndef PMS7003_H
#define PMS7003_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"

#include "mqtt_client.h"

#include "driver/gpio.h"
#include "driver/uart.h"

#include "sensors.h"

/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
#define RX_BUFFER_SIZE 128
#define UART_PMS7003_NUM        UART_NUM_2
#define UART_PMS7003_TXD_PIN    GPIO_NUM_17
#define UART_PMS7003_RXD_PIN    GPIO_NUM_16
#define UART_PMS7003_BAUDRATE   9600

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief Calibrate PM1.0 sensor data.
 * @param raw_pm1_0 Raw PM1.0 data.
 * @return Calibrated PM1.0 data.
 */
float calibrate_pm1_0(float raw_pm1_0);

/**
 * @brief Calibrate PM2.5 sensor data.
 * @param raw_pm2_5 Raw PM2.5 data.
 * @return Calibrated PM2.5 data.
 */
float calibrate_pm2_5(float raw_pm2_5);

/**
 * @brief Calibrate PM10 sensor data.
 * @param raw_pm10 Raw PM10 data.
 * @return Calibrated PM10 data.
 */
float calibrate_pm10(float raw_pm10);

/**
 * @brief Calibrate CO2 sensor data.
 * @param raw_co2 Raw CO2 data.
 * @return Calibrated CO2 data.
 */
float calibrate_co2(float raw_co2);

/**
 * @brief Calibrate temperature sensor data.
 * @param raw_temp Raw temperature data.
 * @return Calibrated temperature data.
 */
float calibrate_temperature(float raw_temp);

/**
 * @brief Calibrate humidity sensor data.
 * @param raw_hum Raw humidity data.
 * @return Calibrated humidity data.
 */
float calibrate_humidity(float raw_hum);

/**
 * @brief Read data from PMS7003 sensor.
 * @param pm1_0 Pointer to store PM1.0 data.
 * @param pm2_5 Pointer to store PM2.5 data.
 * @param pm10 Pointer to store PM10 data.
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t pms7003_readData(uint32_t *pm1_0, uint32_t *pm2_5, uint32_t *pm10);

/**
 * @brief Initialize UART for PMS7003 sensor.
 */
void init_uart_pms7003(void);

/**
 * @brief Task to handle receiving data from PMS7003 sensor.
 * @param arg Pointer to task arguments (unused).
 */
void rx_pms7003_task(void *arg);

#endif // PMS7003_H