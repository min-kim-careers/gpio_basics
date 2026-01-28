#include "http_server.h"
#include "esp_log.h"
#include "esp_http_server.h"

static const char *TAG = "HTTP";

static httpd_handle_t server = NULL;

static esp_err_t status_get_handler(httpd_req_t *req)
{
    httpd_resp_sendstr(req, "ESP32 is alive\n");
    return ESP_OK;
}

static void http_register_endpoints(httpd_handle_t *server)
{
    httpd_uri_t status_uri = {
        .uri = "/status",
        .method = HTTP_GET,
        .handler = status_get_handler,
        .user_ctx = NULL,
    };

    esp_err_t ret = httpd_register_uri_handler(server, &status_uri);
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP handler registered");
    }
    else
    {
        ESP_LOGE(TAG, "HTTP handler failed to register: %d", ret);
    }
}

void http_server_start(void)
{
    // return if server already running
    if (server != NULL)
        return;

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    esp_err_t ret = httpd_start(&server, &config);
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP server started");
        http_register_endpoints(&server);
    }
    else
    {
        ESP_LOGE(TAG, "HTTP server failed to start: %d", ret);
    }
}
