/**
 * @file    mqtt.h
 * @brief   Header file for MQTT client module.
 *
 * @details This file contains the necessary includes, macro definitions,
 *          and function prototypes for the MQTT client module.
 * 
 * @date    June, 2024
 */

#ifndef MQTT_H
#define MQTT_H

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

#include "../sensors/sensors.h"
#include "../main/process.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define MQTT_PUB_VALUE "esp32/test1"    /**< MQTT topic for publishing sensor data */
#define MQTT_BROKER_URI "mqtt://103.1.238.175:1883"  /**< MQTT broker URI */
#define MQTT_USERNAME "test"             /**< MQTT username */
#define MQTT_PASSWORD "testadmin"        /**< MQTT password */

/*******************************************************************************
 * External Variables
 ******************************************************************************/
extern esp_mqtt_client_handle_t client; /**< MQTT client handle */

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
typedef void (*mqtt_handle_t) (char *data, int len); /**< MQTT event handler function pointer */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief MQTT event handler function.
 *
 * This function handles MQTT client events such as connection, disconnection,
 * and message reception.
 *
 * @param[in] handler_args  Handler-specific argument. Not used in current implementation.
 * @param[in] base          Event base associated with the event.
 * @param[in] event_id      Event ID.
 * @param[in] event_data    Pointer to the event data associated with the event.
 */
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

/**
 * @brief Initialize MQTT client.
 *
 * This function initializes the MQTT client configuration and sets up event handling.
 */
void init_mqtt(void);

/**
 * @brief Format sensor data into JSON object.
 *
 * This function formats sensor data into a cJSON object with specified name and value.
 *
 * @param[in,out] object    cJSON object to store formatted data.
 * @param[in]     name      Name of the sensor or data type.
 * @param[in]     value     Sensor data value to be formatted.
 */
void format_data(cJSON *object, const char *name, float value);

/**
 * @brief Task to handle MQTT operations.
 *
 * This task handles the main MQTT operations such as publishing sensor data.
 *
 * @param[in] pvParameters  Parameters passed to the task. Not used in current implementation.
 */
void mqtt_task(void *pvParameters);

#endif // MQTT_H