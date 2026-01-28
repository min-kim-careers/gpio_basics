### FLOW

- `nvs_flash_init()` \
  Initialise NVS (non-volatile storage for WIFI, etc.)

- `esp_netif_init()` \
  Initialise TCP/IP stack

- `esp_event_loop_create_default()` \
  Create system-owned event loop

- `esp_netif_create_default_wifi_sta()` \
  Initialise network interface stack bridging WIFI and TCP/IP

- `esp_wifi_init()` \
  Initialise WIFI stack

- `esp_event_handler_instance_register(<event_type>, <event_handler>, NULL, NULL)` \
  Register event handlers for WIFI and IP events

- `esp_wifi_set_mode(WIFI_MODE_STA)` \
  Set WIFI to STATION mode

- `esp_wifi_set_config(WIFI_IF_STA, &wifi_config)` \
  Apply WIFI config to station

- `esp_wifi_start()` \
  Start WIFI

- `httpd_start(&server, &config)` \
  Start HTTP server (after IP is assigned)

- `httpd_register_uri_handler(server, &<endpoint_uri>)` \
  Register endpoints