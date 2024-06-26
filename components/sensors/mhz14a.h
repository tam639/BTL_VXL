/**
 * @file    mhz14a.h
 * @brief   Header file for interacting with the MH-Z14A sensor.
 *
 * @date    June, 2024
 */

#ifndef MHZ14A_H
#define MHZ14A_H

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

#include "driver/gpio.h"
#include "driver/uart.h"

#include "sensors.h"

/*******************************************************************************
 * Defines and Macros
 ******************************************************************************/
#define RX_BUF_SIZE             1024              ///< Receive buffer size for UART
#define UART_MHZ14A_NUM         UART_NUM_1        ///< UART port number for MH-Z14A
#define UART_MHZ14A_TXD_PIN     GPIO_NUM_23       ///< UART TX pin for MH-Z14A
#define UART_MHZ14A_RXD_PIN     GPIO_NUM_5        ///< UART RX pin for MH-Z14A
#define UART_MHZ14A_BAUDRATE    9600              ///< Baud rate for MH-Z14A UART communication

/*******************************************************************************
 * Function Declarations
 ******************************************************************************/

/**
 * @brief Initialize UART for MH-Z14A sensor.
 */
void init_uart_mhz14a(void);

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
int transmit_uart_mhz14a(const char* logName, uart_port_t uart_num, const char* data, const int len);

/**
 * @brief Task to handle receiving data from MH-Z14A sensor.
 * 
 * @param arg Pointer to task arguments (unused).
 */
void rx_mhz14a_task(void *arg);

#endif // MHZ14A_H