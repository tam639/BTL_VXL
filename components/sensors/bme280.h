/**
 * @file    bmx280.h
 * @brief   Header file for BMX280 sensor driver.
 *
 * @details Contains definitions, prototypes, and includes for interfacing with
 *          the BMX280 sensor via I2C. Provides functions for sensor initialization,
 *          configuration, mode setting, and data reading (fixed-point and floating-point).
 *
 * @date    June, 2024
 */
#ifndef _BMX280_H_
#define _BMX280_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <limits.h>
#include "driver/i2c.h"
#include "sdkconfig.h"

#include "sensors.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BMXAPI extern

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Anonymous structure for driver settings.
 */
typedef struct bmx280_t bmx280_t;

#include "bmx280_bits.h"

/**
 * @brief Create an instance of the BMX280 driver.
 * @param port The I2C port to use.
 * @return A non-null pointer to the driver structure on success.
 */
BMXAPI bmx280_t* bmx280_create(i2c_port_t port);

/**
 * @brief Destroy the instance.
 * @param bmx280 The instance to destroy.
 */
BMXAPI void bmx280_close(bmx280_t* bmx280);

/**
 * @brief Probe for the sensor and read calibration data.
 * @param bmx280 Driver structure.
 * @return ESP_OK on success, or an error code on failure.
 */
BMXAPI esp_err_t bmx280_init(bmx280_t* bmx280);

/**
 * @brief Configure the sensor with the given parameters.
 * @param bmx280 Driver structure.
 * @param configuration The configuration to use.
 * @return ESP_OK on success, or an error code on failure.
 */
BMXAPI esp_err_t bmx280_configure(bmx280_t* bmx280, bmx280_config_t *cfg);

/**
 * @brief Set the sensor mode of operation.
 * @param bmx280 Driver structure.
 * @param mode The mode to set the sensor to.
 * @return ESP_OK on success, or an error code on failure.
 */
BMXAPI esp_err_t bmx280_setMode(bmx280_t* bmx280, bmx280_mode_t mode);

/**
 * @brief Get the sensor current mode of operation.
 * @param bmx280 Driver structure.
 * @param mode Pointer to write current mode to.
 * @return ESP_OK on success, or an error code on failure.
 */
BMXAPI esp_err_t bmx280_getMode(bmx280_t* bmx280, bmx280_mode_t* mode);

/**
 * @brief Returns true if sensor is currently sampling environment conditions.
 * @param bmx280 Driver structure.
 * @return true if sampling, false otherwise.
 */
BMXAPI bool bmx280_isSampling(bmx280_t* bmx280);

/**
 * @brief Read sensor values as fixed point numbers.
 * @param bmx280 Driver structure.
 * @param temperature The temperature in C (0.01 degree C increments).
 * @param pressure The pressure in Pa (1/256 Pa increments).
 * @param humidity The humidity in %RH (1/1024 %RH increments) (UINT32_MAX when invalid).
 * @return ESP_OK on success, or an error code on failure.
 */
BMXAPI esp_err_t bmx280_readout(bmx280_t *bmx280, int32_t *temperature, uint32_t *humidity);

/**
 * @brief Convert sensor readout to floating point values.
 * @param tin Input temperature.
 * @param pin Input pressure.
 * @param hin Input humidity.
 * @param tout Output temperature (C).
 * @param pout Output pressure (Pa).
 * @param hout Output humidity (%RH).
 */
static inline void bmx280_readout2float(int32_t* tin, uint32_t *hin, float *tout, float *hout)
{
    if (tin && tout)
        *tout = (float)*tin * 0.01f;
    // if (pin && pout)
    //     *pout = (float)*pin * (1.0f/256.0f);
    if (hin && hout)
        *hout = (*hin == UINT32_MAX) ? -1.0f : (float)*hin * (1.0f/1024.0f);
}

/**
 * @brief Read sensor values as floating point numbers.
 * @param bmx280 Driver structure.
 * @param temperature The temperature in C.
 * @param pressure The pressure in Pa.
 * @param humidity The humidity in %RH.
 * @return ESP_OK on success, or an error code on failure.
 */
static inline esp_err_t bmx280_readoutFloat(bmx280_t *bmx280, float* temperature, float* humidity)
{
    int32_t t; uint32_t h;
    esp_err_t err = bmx280_readout(bmx280, &t, &h);

    if (err == ESP_OK)
    {
        bmx280_readout2float(&t, &h, temperature, humidity);
    }

    return err;
}

/**
 * @brief Initialize the I2C communication for BME280.
 */
void init_i2c_bme280(void);

/**
 * @brief Task to handle BME280 I2C communication.
 * @param arg Arguments for the task.
 */
void i2c_bme280_task(void *arg);

#ifdef __cplusplus
}
#endif

#endif /* _BMX280_H_ */