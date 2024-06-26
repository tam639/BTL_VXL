idf_component_register(SRCS "wifi.c" "mqtt.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver json esp_wifi esp_timer esp-tls app_update mqtt esp_lcd main sensors)