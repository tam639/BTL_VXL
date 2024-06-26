/**
 * @file    process.h
 * @brief   Header file for the process module.
 *
 * @details This file contains the necessary includes, macro definitions,
 *          and function prototypes for the process module.
 * 
 * @date    June, 2024
 */

#ifndef PROCESS_H
#define PROCESS_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/param.h>
#include "cJSON.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_tls.h"
#include "esp_ota_ops.h"
#include "esp_smartconfig.h"
#include "esp_sleep.h"

#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "mqtt_client.h"

#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/rtc_io.h"

#include "lvgl.h"
#include "ui.h"
#include "esp_lcd_ili9341.h"

#include <inttypes.h>

#include "wifi.h"
#include "mqtt.h"
#include "ili9341.h"
#include "sensors.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern QueueHandle_t sensorDataQueue;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief Initialize the sensor data queue.
 */
void init_queue(void);

/**
 * @brief Initialize the application.
 */
void app_init(void);

/**
 * @brief Main application task.
 */
void app_task(void);

#endif // PROCESS_H