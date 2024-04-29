#ifndef __SSD1306__
#define __SSD1306__

typedef void (* ssd1306_init_fail_callback_t)(void);
void ssd1306_init(ssd1306_init_fail_callback_t cb);
void ssd1306_display_celsius(double value);

#endif