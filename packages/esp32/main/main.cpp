#include "Arduino.h"
#include "Wire.h"
#include "buzz.h"
#include "ssd1306.h"
#include "mlx.h"
#include "ble.h"
#include "config.h"

#define WARNING_TEMP 38

// esp32c3
#define SDA_PIN GPIO_NUM_8
#define SCL_PIN GPIO_NUM_9

SemaphoreHandle_t binarySemaphoreHandle = NULL;

volatile double temperature;

uint8_t refineCelsiusForHuman(double temperature, double *outCelsius) {
  if (temperature < 32) {
    return 1;
  }

  if (temperature > 45) {
    *outCelsius = 45;
  }
  else {
    *outCelsius = temperature;
  }

  return 0;
} 

void task_detect_temperature(void *param) {
  while (1) {
    temperature = mlx_get_celsius();
    xSemaphoreGive(binarySemaphoreHandle);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void task_react_temperature(void *param) {
  while (1) {
    if (xSemaphoreTake(binarySemaphoreHandle, portMAX_DELAY) != pdTRUE) continue;

    // Refine the temperature according to the type of target being detected.
    uint8_t target = config_get_target();
    double warning_celsius = config_get_warning_celsius();
    double celsius = temperature;
    uint8_t ret_code = 0;
    if (target == 0) {
      ret_code = refineCelsiusForHuman(temperature, &celsius);
    }

    if (ret_code == 0) {
      ssd1306_display_celsius(celsius);
      ble_set_celsius(celsius, ret_code);

      // turn on the red led and buzz.
      if (celsius >= warning_celsius) {
        buzz_on();
      }
      else {
        buzz_off();
      }
    }
    else {
      ssd1306_display_celsius(celsius);
      ble_set_celsius(celsius, ret_code);
    }
  }
}

void ssd1306_init_failed_callback(void) {
  printf("SSD1306 allocation failed\n");
  for(uint8_t i = 6; i > 0; --i) {
    buzz_toggle();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

extern "C" void app_main()
{
  initArduino();

  config_init();
  buzz_init();
  ble_init();
  // Initialize the first I2C
  if (Wire.begin(SDA_PIN, SCL_PIN)) {
    ssd1306_init(ssd1306_init_failed_callback);
    // Initialize MLX90614
    mlx_init();
  }

  binarySemaphoreHandle = xSemaphoreCreateBinary();
  xTaskCreate(task_detect_temperature, "task_detect_temperature", 1024*2, NULL, 0, NULL);
  xTaskCreate(task_react_temperature, "task_react_temperature", 1024*4, NULL, 0, NULL);
}