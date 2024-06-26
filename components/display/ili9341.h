/**
 * @file    ili9341.h
 * @brief   Header file for ILI9341 LCD display driver.
 *
 * @details This file includes necessary headers, macro definitions,
 *          and function prototypes for the ILI9341 LCD driver.
 * 
 * @date    June, 2024
 */

#ifndef ILI9341_H
#define ILI9341_H

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
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "lvgl.h"
#include "ui.h"
#include "esp_lcd_ili9341.h"

#include <inttypes.h>

#include "../sensors/sensors.h"
#include "../main/process.h"

/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           14
#define EXAMPLE_PIN_NUM_MOSI           13
#define EXAMPLE_PIN_NUM_MISO           12
#define EXAMPLE_PIN_NUM_LCD_DC         2
#define EXAMPLE_PIN_NUM_LCD_RST        33
#define EXAMPLE_PIN_NUM_LCD_CS         15
#define EXAMPLE_PIN_NUM_BK_LIGHT       32
#define EXAMPLE_PIN_NUM_TOUCH_CS       35

// The pixel number in horizontal and vertical
#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              320

// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (4 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     2

/*******************************************************************************
 * External Declarations
 ******************************************************************************/
extern SemaphoreHandle_t lvgl_mux;

/**
 * @brief Initialize the user interface (UI).
 */
extern void ui_init();

/**
 * @brief Notify LVGL that the flush is ready.
 *
 * @param panel_io Pointer to the LCD panel IO handle.
 * @param edata Pointer to the event data.
 * @param user_ctx User context.
 * @return true if notification is successful, false otherwise.
 */
bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);

/**
 * @brief LVGL flush callback function.
 *
 * @param drv Pointer to the display driver structure.
 * @param area Pointer to the area to flush.
 * @param color_map Pointer to the color map.
 */
void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);

/**
 * @brief Increase LVGL tick.
 *
 * @param arg Argument passed to the function.
 */
void example_increase_lvgl_tick(void *arg);

/**
 * @brief Initialize the ILI9341 LCD display.
 */
void init_ili9341(void);

/**
 * @brief Task to handle display operations.
 *
 * @param pvParameters Task parameters.
 */
void display_task(void *pvParameters);

#endif // ILI9341_H