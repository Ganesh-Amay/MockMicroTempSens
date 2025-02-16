#pragma once

#include <cstdint>

// Example pin definitions
enum class GpioPin : uint8_t
{
    LED_GREEN,
    LED_YELLOW,
    LED_RED
};

// Initialize a GPIO pin as output
void Gpio_InitPin(GpioPin pin);

// Set or reset the pin output
void Gpio_WritePin(GpioPin pin, bool state);
