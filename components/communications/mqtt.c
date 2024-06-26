/**
 * @file    mqtt.c
 * @brief   MQTT functionalities implementation.
 *
 * @details This file contains implementations for MQTT initialization,
 *          event handling, data formatting, and task for publishing sensor data.
 *
 * @date    June, 2024
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "mqtt.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const char *TAG = "MQTT_PROJECT";
uint32_t MQTT_CONNECTED = 0;
esp_mqtt_client_handle_t client = NULL;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief MQTT event handler.
 *
 * This function handles various MQTT events such as connection and disconnection.
 *
 * @param handler_args Handler arguments (not used).
 * @param base Event base.
 * @param event_id Event ID.
 * @param event_data Event data.
 */
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    client = event->client;

    switch (event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        MQTT_CONNECTED = 1;
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        MQTT_CONNECTED = 0;
        esp_mqtt_client_reconnect(client);
        break;
    default:
        break;
    }
}

/**
 * @brief Initialize MQTT client.
 *
 * This function initializes the MQTT client with the provided configuration.
 */
void init_mqtt(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER_URI,
        .credentials.username = MQTT_USERNAME,
        .credentials.authentication.password = MQTT_PASSWORD,
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}

/**
 * @brief Format data into JSON format.
 *
 * This function formats data into JSON format and adds it to the provided cJSON object.
 *
 * @param object cJSON object to which data will be added.
 * @param name Name of the data field.
 * @param value Value to be formatted.
 */
void format_data(cJSON *object, const char *name, float value)
{
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    cJSON_AddStringToObject(object, name, buffer);
}

/**
 * @brief MQTT task for publishing sensor data.
 *
 * This task publishes sensor data in JSON format via MQTT.
 *
 * @param pvParameters Task parameters (not used).
 */
void mqtt_task(void *pvParameters)
{
    ESP_ERROR_CHECK(esp_smartconfig_set_type(SC_TYPE_ESPTOUCH));
    smartconfig_start_config_t cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_smartconfig_start(&cfg));

    while (true)
    {
        if (xQueueReceive(sensorDataQueue, &sensorData, portMAX_DELAY) == pdPASS)
        {
            printf("\nAvailable after dequeue: %d \n\n", uxQueueSpacesAvailable(sensorDataQueue));

            cJSON *root = cJSON_CreateObject();

            format_data(root, "timestamp", sensorData.timestamp);
            format_data(root, "temperature", sensorData.temperature);
            format_data(root, "humidity", sensorData.humidity);
            format_data(root, "pm1_0", sensorData.pm1_0);
            format_data(root, "pm2_5", sensorData.pm2_5);
            format_data(root, "pm10", sensorData.pm10);
            format_data(root, "CO2", sensorData.CO2);

            char *json_string = cJSON_Print(root);
            esp_mqtt_client_publish(client, MQTT_PUB_VALUE, json_string, 0, 1, 0);
            cJSON_Delete(root);
            free(json_string);
        }
        else 
        {
            printf("Error Transfer!\n");
        }
    }
}