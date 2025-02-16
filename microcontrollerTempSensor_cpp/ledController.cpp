#include "ledController.h"
#include "driver_gpio.h"

// LED thresholds:
// Red: T < 5°C or T >= 105°C
// Yellow: 85°C <= T < 105°C
// Green: 5°C <= T < 85°C

void LedController::init() {
  Gpio_InitPin(GpioPin::LED_GREEN);
  Gpio_InitPin(GpioPin::LED_YELLOW);
  Gpio_InitPin(GpioPin::LED_RED);
}

void LedController::setGreen(bool state) {
  Gpio_WritePin(GpioPin::LED_GREEN, state);
}

void LedController::setYellow(bool state) {
  Gpio_WritePin(GpioPin::LED_YELLOW, state);
}

void LedController::setRed(bool state) {
  Gpio_WritePin(GpioPin::LED_RED, state);
}

void LedController::update(float temperatureC) {
  bool red = (temperatureC < 5.0f) || (temperatureC >= 105.0f);
  bool yellow = (temperatureC >= 85.0f && temperatureC < 105.0f);
  bool green = (temperatureC >= 5.0f && temperatureC < 85.0f);

  setRed(red);
  setYellow(yellow);
  setGreen(green);
}
