#include "driver/gpio.h"
#include "buzz.h"

#define BUZZ_PIN GPIO_NUM_5

void buzz_init(void) {
  gpio_reset_pin(BUZZ_PIN);
  gpio_set_direction(BUZZ_PIN, GPIO_MODE_INPUT_OUTPUT);
}

void buzz_on(void) {
  gpio_set_level(BUZZ_PIN, 1);
}

void buzz_off(void) {
  gpio_set_level(BUZZ_PIN, 0);
}

void buzz_toggle(void) {
  gpio_set_level(BUZZ_PIN, gpio_get_level(BUZZ_PIN));
}
