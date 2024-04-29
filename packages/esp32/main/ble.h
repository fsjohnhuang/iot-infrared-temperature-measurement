#ifndef __BLE__
#define __BLE__

void ble_init(void);
void ble_set_celsius(double value, uint8_t ret_code);
void ble_set_warn(uint8_t value);

#endif