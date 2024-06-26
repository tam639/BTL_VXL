/**
 * @file    ui.h
 * @brief   Header file for UI management.
 *
 * @details This file declares functions and variables related to UI initialization
 *          and component management using LVGL library.
 *
 * @date    June, 2024
 */

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../../managed_components/lvgl__lvgl/lvgl.h"   ///< LVGL library for graphical interface
#include "ui_helpers.h"    ///< Helper functions for UI management
#include <inttypes.h>     ///< Standard integer types
#include "sensors.h"       ///< Sensor data structures and functions

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Initialize the UI components.
 */
void ui_init(void);

/**
 * @brief Initialize Screen 1 of the UI.
 *
 * @details This function initializes all UI elements for Screen 1.
 */
void ui_Screen1_screen_init();

extern lv_obj_t * ui_Screen1;    ///< Screen 1 object
extern lv_obj_t * ui_Panel1;     ///< Panel 1 object
extern lv_obj_t * ui_airsense1;  ///< Airsense icon object
extern lv_obj_t * ui_wifi1;      ///< WiFi icon object
extern lv_obj_t * ui_battery1;   ///< Battery icon object
extern lv_obj_t * ui_humi;       ///< Humidity icon object
extern lv_obj_t * ui_Co2;        ///< CO2 icon object
extern lv_obj_t * ui_Label1;     ///< Label 1 object
extern lv_obj_t * ui_Label2;     ///< Label 2 object
extern lv_obj_t * ui_Label3;     ///< Label 3 object
extern lv_obj_t * ui_Image1;     ///< Image 1 object
extern lv_obj_t * ui_Image2;     ///< Image 2 object
extern lv_obj_t * ui_Image3;     ///< Image 3 object
extern lv_obj_t * ui_Label7;     ///< Label 7 object
extern lv_obj_t * ui_Label8;     ///< Label 8 object
extern lv_obj_t * ui_Label9;     ///< Label 9 object
extern lv_obj_t * ui____initial_actions0;   ///< Initial actions object

LV_IMG_DECLARE(ui_img_airsense_png);    // assets/airsense.png
LV_IMG_DECLARE(ui_img_wwifi1_png);      // assets/wwifi1.png
LV_IMG_DECLARE(ui_img_batterry_png);    // assets/battery.png
LV_IMG_DECLARE(ui_img_co2_png);         // assets/CO2.png
LV_IMG_DECLARE(ui_img_temp_png);        // assets/temp.png
LV_IMG_DECLARE(ui_img_humi_png);        // assets/humi.png
LV_IMG_DECLARE(ui_img_next1_png);       // assets/next1.png
LV_IMG_DECLARE(ui_img_next2_png);       // assets/next2.png

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _SQUARELINE_PROJECT_UI_H */