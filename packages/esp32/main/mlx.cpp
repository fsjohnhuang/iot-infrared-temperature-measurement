#include "Adafruit_MLX90614.h"
#include "mlx.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void mlx_init(void) {
  mlx.begin();
}

double mlx_get_celsius(void) {
  return mlx.readObjectTempC();
}