idf_component_register(SRCS "ili9341.c" "ui.c" "ui_helpers.c" "images/ui_img_humirz1_png.c" 
                            "images/ui_img_co2_png.c" "images/ui_img_humi_png.c" 
                            "images/ui_img_temp_png.c" "images/ui_img_airsense_png.c" 
                            "images/ui_img_batterry_png.c" "images/ui_img_wwifi1_png.c"
                        INCLUDE_DIRS "."
                        REQUIRES driver json esp_wifi esp_timer esp-tls app_update mqtt 
                                esp_lcd lwip lvgl__lvgl espressif__esp_lcd_ili9341 main sensors)