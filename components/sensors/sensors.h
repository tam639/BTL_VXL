/**
 * @file    sensors.h
 * @brief   Header file for sensor handling module.
 *
 * @details This file defines the structures, includes necessary libraries,
 *          and declares function prototypes related to sensor handling.
 * 
 * @date    June, 2024
 */

#ifndef SENSORS_H
#define SENSORS_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "mhz14a.h"
#include "pms7003.h"
#include "bme280.h"

#include "../main/process.h"

/*******************************************************************************
 * Data Structures
 ******************************************************************************/
typedef struct {
    uint64_t timestamp; ///< Timestamp of sensor data.

    float temperature; ///< Temperature data from BME280.
    float humidity;    ///< Humidity data from BME280.

    float pm1_0; ///< PM1.0 particle concentration from PMS7003.
    float pm2_5; ///< PM2.5 particle concentration from PMS7003.
    float pm10;  ///< PM10 particle concentration from PMS7003.

    float CO2;   ///< CO2 concentration from MH-Z14A.
} SensorData;

/*******************************************************************************
 * External Variables
 ******************************************************************************/
extern SensorData sensorData; ///< External variable holding sensor data.

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief Initialize sensors.
 */
void init_sensors(void);

/**
 * @brief Task to handle sensor data acquisition.
 * @param arg Pointer to task arguments (unused).
 */
void sensor_task(void *arg);

#endif // SENSORS_H