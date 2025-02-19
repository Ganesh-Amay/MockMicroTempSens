#include "ledController.h"
#include "driver_gpio.h"
#include <stdbool.h>

// LED thresholds:
// Red: T < 5°C or T >= 105°C
// Yellow: 85°C <= T < 105°C
// Green: 5°C <= T < 85°C

void LedController_init(void) {
  Gpio_InitPin(LED_GREEN);
  Gpio_InitPin(LED_YELLOW);
  Gpio_InitPin(LED_RED);
}

void LedController_setGreen(int on) {
  Gpio_WritePin(LED_GREEN, on ? true : false);
}

void LedController_setYellow(int on) {
  Gpio_WritePin(LED_YELLOW, on ? true : false);
}

void LedController_setRed(int on) { Gpio_WritePin(LED_RED, on ? true : false); }

void LedController_update(float temperatureC) {
  bool red = (temperatureC < 5.0f) || (temperatureC >= 105.0f);
  bool yellow = (temperatureC >= 85.0f && temperatureC < 105.0f);
  bool green = (temperatureC >= 5.0f && temperatureC < 85.0f);

  LedController_setRed(red);
  LedController_setYellow(yellow);
  LedController_setGreen(green);
}
