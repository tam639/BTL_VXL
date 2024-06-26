/**
 * @file    wifi.h
 * @brief   Header file for WiFi functionality.
 *
 * @details This file defines functions and constants related to WiFi setup
 *          and management.
 */

#ifndef WIFI_H
#define WIFI_H

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
#include "esp_netif.h"
#include "esp_tls.h"
#include "esp_ota_ops.h"
#include "esp_smartconfig.h"

#include "mqtt_client.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define WIFI_CONNECTED_BIT      BIT0    /**< WiFi connected event bit */
#define ESPTOUCH_DONE_BIT       BIT1    /**< ESP-Touch configuration done event bit */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief WiFi event handler function.
 *
 * This function handles WiFi events such as connection, disconnection, etc.
 *
 * @param[in] arg           Pointer to an argument passed to the event handler.
 * @param[in] event_base    Event base associated with the event.
 * @param[in] event_id      Event ID.
 * @param[in] event_data    Pointer to the event data associated with the event.
 */
void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

/**
 * @brief Initialize WiFi functionality.
 *
 * This function initializes WiFi subsystem and sets up event handling.
 */
void init_wifi();

#endif // WIFI_H