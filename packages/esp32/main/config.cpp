#include "nvs_flash.h"
#include "esp_log.h"

#define TAG "config"
#define NAMESPACE "config"
#define DEFAULT_TARGET 0 // 0 - human being

void config_init() {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    // erase the whole SPI flash if no space leaves or new version has been found.
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
  }

  nvs_handle_t nvs_handle;
  err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "opening NVS Error (%s)\n", esp_err_to_name(err));
  }
  else {
    ESP_LOGI(TAG, "NVS open OK\n");
  }

  uint8_t value;
  err = nvs_get_u8(nvs_handle, "target", &value);
  if (err != ESP_OK) {
    err = nvs_set_u8(nvs_handle, "target", DEFAULT_TARGET);
  }

  err = nvs_commit(nvs_handle);
  if(err!=ESP_OK) ESP_LOGE(TAG, "nvs_commit Error");

  //关闭
  nvs_close(nvs_handle);
}

uint8_t config_get_target(void) {
  nvs_handle_t nvs_handle;
  esp_err_t err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "opening NVS Error (%s)\n", esp_err_to_name(err));
  }

  uint8_t value;
  err = nvs_get_u8(nvs_handle, "target", &value);
  if (err != ESP_OK) {
    value = DEFAULT_TARGET;
    err = nvs_set_u8(nvs_handle, "target", DEFAULT_TARGET);
  }

  err = nvs_commit(nvs_handle);
  if(err!=ESP_OK) ESP_LOGE(TAG, "nvs_commit Error");

  //关闭
  nvs_close(nvs_handle);

  return value;
}

void config_set_target(uint8_t value) {
  nvs_handle_t nvs_handle;
  esp_err_t err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "opening NVS Error (%s)\n", esp_err_to_name(err));
  }
  else {
    ESP_LOGI(TAG, "NVS open OK\n");
  }

  nvs_set_u8(nvs_handle, "target", value);

  err = nvs_commit(nvs_handle);
  if(err!=ESP_OK) ESP_LOGE(TAG, "nvs_commit Error");

  //关闭
  nvs_close(nvs_handle);
}

double config_get_warning_celsius(void) {
  return 38;
}