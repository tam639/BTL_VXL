idf_component_register(SRCS "sensors.c" "mhz14a.c" "pms7003.c" "bme280.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver json esp_wifi esp_timer esp-tls app_update mqtt esp_lcd 
                            lwip lvgl__lvgl espressif__esp_lcd_ili9341 main)