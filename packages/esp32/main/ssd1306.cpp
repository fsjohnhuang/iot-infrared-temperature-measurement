#include "Wire.h"
#include "Adafruit_SSD1306.h"
#include "ssd1306.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define RESET -1
#define ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, RESET);

static void ssd1306_splash(void) {
  display.clearDisplay();
  display.setTextSize(1);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0); 
  display.println("Infrared Temperature Detector Is Loading...");
  display.display();

  vTaskDelay(pdMS_TO_TICKS(1000));
  display.clearDisplay();
}

void ssd1306_init(ssd1306_init_fail_callback_t cb) {
  if (!display.begin(SSD1306_SWITCHCAPVCC, ADDRESS)) {
    if (cb != NULL) {
      cb();
    }
    esp_restart();
  }
  else {
    ssd1306_splash();
  }
}

void ssd1306_display_celsius(double value) {
  // Show current temperature in SSD1306
  char str[20];
  sprintf(str, "Temp: %.1f", value);
  display.clearDisplay();

  display.setTextSize(1);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0); 
  display.println("Infrared Temperature Detector Is Working...");
  display.setTextSize(2);           
  display.setCursor(0, 20); 
  display.println(str);

  display.display(); 
}