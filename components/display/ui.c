/**
 * @file    ui.c
 * @brief   User Interface functions for displaying sensor data.
 *
 * @date    June, 2024
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ui.h"
#include <inttypes.h>
#include "esp_log.h"
#include <string.h>
#include <stdio.h>
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
// Get Data from sensors
SensorData *Get_Data_Sensor(void)
{
    return &sensorData;
}

// SCREEN: ui_Screen1
void ui_Screen1_screen_init();
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_airsense1;
lv_obj_t * ui_wifi1;
lv_obj_t * ui_battery1;
lv_obj_t * ui_humi;
lv_obj_t * ui_Co2;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Image2;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Label7;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Label9;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_next[2] = {&ui_img_next1_png, &ui_img_next2_png};
const lv_img_dsc_t * ui_imgset_wwifi[1] = {&ui_img_wwifi1_png};
const lv_img_dsc_t * ui_imgset_co[1] = {&ui_img_co2_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_Screen1_screen_init(void)
{
    char buffer[32];
    SensorData *sensor_data;
    sensor_data = &sensorData;
    float temp_data = sensor_data->temperature;
    float humi_data = sensor_data->humidity;
    float Co2_data = sensor_data->CO2;
    float pm1_0_data = sensor_data->pm1_0;
    float pm2_5_data = sensor_data->pm2_5;
    float pm10_data = sensor_data->pm10;
    
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, 255);
    lv_obj_set_height(ui_Panel1, 330);
    lv_obj_set_x(ui_Panel1, -1);
    lv_obj_set_y(ui_Panel1, -5);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x020202), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_airsense1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_airsense1, &ui_img_airsense_png);
    lv_obj_set_width(ui_airsense1, LV_SIZE_CONTENT);   /// 80
    lv_obj_set_height(ui_airsense1, LV_SIZE_CONTENT);    /// 80
    lv_obj_set_x(ui_airsense1, -77);
    lv_obj_set_y(ui_airsense1, -134);
    lv_obj_set_align(ui_airsense1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_airsense1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_airsense1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_wifi1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_wifi1, &ui_img_wwifi1_png);
    lv_obj_set_width(ui_wifi1, LV_SIZE_CONTENT);   /// 40
    lv_obj_set_height(ui_wifi1, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_x(ui_wifi1, 25);
    lv_obj_set_y(ui_wifi1, -132);
    lv_obj_set_align(ui_wifi1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_wifi1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_battery1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_battery1, &ui_img_batterry_png);
    lv_obj_set_width(ui_battery1, LV_SIZE_CONTENT);   /// 40
    lv_obj_set_height(ui_battery1, LV_SIZE_CONTENT);    /// 22
    lv_obj_set_x(ui_battery1, 77);
    lv_obj_set_y(ui_battery1, -131);
    lv_obj_set_align(ui_battery1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_battery1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_battery1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_battery1, 300);


    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -12);
    lv_obj_set_y(ui_Label1, -82);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    ESP_LOGI(__func__, "temp:%.2f", temp_data);
    snprintf(buffer, sizeof(buffer), "TEMP : %.2f °C", temp_data);
    ESP_LOGI(__func__, "Buffer: %s", buffer);
    lv_label_set_text(ui_Label1, buffer);
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xE51D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, 5);
    lv_obj_set_y(ui_Label2, 2);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    ESP_LOGI(__func__, "Co2:%.2f", Co2_data);
    snprintf(buffer, sizeof(buffer), "Co2 : %.2f ppm", Co2_data);
    ESP_LOGI(__func__, "Buffer: %s", buffer);
    lv_label_set_text(ui_Label2, buffer);
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x2AF69D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -14);
    lv_obj_set_y(ui_Label3, -41);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    ESP_LOGI(__func__, "Humi:%.2f", humi_data);
    snprintf(buffer, sizeof(buffer), "HUMI : %.2f %%", humi_data);
    ESP_LOGI(__func__, "Buffer: %s", buffer);
    lv_label_set_text(ui_Label3, buffer);
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0x2E60E7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image1, &ui_img_co2_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 35
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 35
    lv_obj_set_x(ui_Image1, -90);
    lv_obj_set_y(ui_Image1, 5);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image2 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image2, &ui_img_temp_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);   /// 35
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);    /// 33
    lv_obj_set_x(ui_Image2, -91);
    lv_obj_set_y(ui_Image2, -86);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image3 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image3, &ui_img_humi_png);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 35
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 31
    lv_obj_set_x(ui_Image3, -88);
    lv_obj_set_y(ui_Image3, -42);
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label7 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, -1);
    lv_obj_set_y(ui_Label7, 55);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    snprintf(buffer, sizeof(buffer), "PM 1.0 : %.2f ug/m3", pm1_0_data);
        lv_label_set_text(ui_Label7, buffer);
    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x2AE3F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label8, -1);
    lv_obj_set_y(ui_Label8, 81);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    snprintf(buffer, sizeof(buffer), "PM 2.5 : %.2f ug/m3", pm2_5_data);
    lv_label_set_text(ui_Label8, buffer);
    lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0x2AE3F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, 2);
    lv_obj_set_y(ui_Label9, 117);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    snprintf(buffer, sizeof(buffer), "PM 10 : %.2f ug/m3", pm10_data);
    lv_label_set_text(ui_Label9, buffer);
    lv_obj_set_style_text_color(ui_Label9, lv_color_hex(0x2AE3F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
