#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "nvs_flash.h"


#define AP_SSID "ESPTEST"
#define AP_PASSWORD "MRAASMM1468"
#define AP_MAX_CONN 4
#define AP_CHANNEL 0

#define LED 18

void app_main(void)
{
    
    /*nvs_flash_deinit();
    tcpip_adapter_init();
    wifi_init_config_t wifi_config=WIFI_INIT_CONFIG_DEFAULT(); 
    esp_wifi_init(&wifi_config);
    esp_wifi_set_mode(WIFI_MODE_AP);

    wifi_config_t ap_config={.ap={.ssid=AP_SSID,.password=AP_PASSWORD,.max_connection=AP_MAX_CONN,.channel=AP_CHANNEL,.ssid_hidden=0},};
    esp_wifi_set_config(ESP_IF_WIFI_AP,&ap_config);
    esp_wifi_start();*/

    gpio_set_direction(LED,GPIO_MODE_DEF_OUTPUT);
    while (1)
    {
        gpio_set_level(LED,0);
        vTaskDelay(100);
        gpio_set_level(LED,1);
        vTaskDelay(100);
    }
}
