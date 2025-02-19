#pragma once

#include <stdbool.h>

// Mock pin definitions
typedef enum GpioPin { LED_GREEN, LED_YELLOW, LED_RED } GpioPin;

// Mock Initialize a GPIO pin as output
void Gpio_InitPin(GpioPin pin);

// Mock Set or reset the pin output
void Gpio_WritePin(GpioPin pin, bool state);
