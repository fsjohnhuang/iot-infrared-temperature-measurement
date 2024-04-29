#ifndef __CONFIG__
#define __CONFIG__

#include <stdint.h>

void config_init(void);
uint8_t config_get_target(void);
void config_set_target(uint8_t);
double config_get_warning_celsius(void);
void config_set_warning_celsius(double);
#endif