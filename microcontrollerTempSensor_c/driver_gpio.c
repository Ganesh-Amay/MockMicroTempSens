

#include "driver_gpio.h"
#include <stdio.h>

void Gpio_InitPin(GpioPin pin) {
  // Real code: config MODER to output or analog, etc.
  switch (pin) {
  case LED_GREEN:
    printf("[GPIO] Init Green LED as output\n");
    break;
  case LED_YELLOW:
    printf("[GPIO] Init Yellow LED as output\n");
    break;
  case LED_RED:
    printf("[GPIO] Init Red LED as output\n");
    break;
  }
}

void Gpio_WritePin(GpioPin pin, bool state) {
  // Real code: set or clear ODR bit
  switch (pin) {
  case LED_GREEN:
    if (state)
      printf("Green ON\n");
    else
      printf("Green OFF\n");
    break;
  case LED_YELLOW:
    if (state)
      printf("Yellow ON\n");
    else
      printf("Yellow OFF\n");
    break;
  case LED_RED:
    if (state)
      printf("Red ON\n");
    else
      printf("Red OFF\n");
    break;
  }
}
