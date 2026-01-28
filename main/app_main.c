#include "wifi.c"
#include "esp_sleep.h"

static void deep_sleep()
{
    ESP_LOGI("SLEEP", "deep sleep enabled...");
    esp_deep_sleep_start();
}

void app_main(void)
{
    // wifi_init_sta();
    deep_sleep();
}