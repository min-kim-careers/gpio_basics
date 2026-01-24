#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "wifi_secrets.h"

static const char *TAG = "WIFI_LOG";

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT)
    {
        if (event_id == WIFI_EVENT_STA_START)
        {
            ESP_LOGI(TAG, "WIFI_EVENT_STA_START -> connect");
            esp_err_t r = esp_wifi_connect();
            if (r != ESP_OK)
                ESP_LOGW(TAG, "esp_wifi_connect() returned %d", r);
        }
        else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            ESP_LOGW(TAG, "STA disconneced, retrying...");
            esp_wifi_connect();
        }
        else if (event_id == WIFI_EVENT_STA_CONNECTED)
        {
            ESP_LOGI(TAG, "STA connected");
        }
    }
}

void wifi_init_sta(void)
{
    // init nvs (non-volatile storage)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    // init and start network stack
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // set up wifi interface (links with above)
    esp_netif_create_default_wifi_sta();

    // wifi config
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS},
    };

    // wifi driver with default settings
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // init driver
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    // set to station mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    // apply wifi config to station
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    esp_err_t reg_err = esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);
    ESP_LOGI(TAG, "wifi handler registered: %d", reg_err);

    ESP_ERROR_CHECK(esp_wifi_start());
}