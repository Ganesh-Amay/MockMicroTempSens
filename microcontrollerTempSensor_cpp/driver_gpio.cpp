

#include "driver_gpio.h"
#include <cstdio>

void Gpio_InitPin(GpioPin pin) {
  // Real code: config MODER to output or analog, etc.
  /* The MODER register selects whether a GPIO pin is:
  ** 00 → Input Mode
  ** 01 → Output Mode
  ** 10 → Alternate Function Mode (used for peripherals like UART, SPI, etc.)
  ** 11 → Analog Mode (used for ADC input)
  ** GPIOA->MODER &= ~(3 << (2 * 5));  // Clear bits for PA5
  ** GPIOA->MODER |= (1 << (2 * 5));   // Set PA5 as output
  * For ADC input, the pin should be set to analog mode:
  ** GPIOA->MODER |= (3 << (2 * 0));  // PA0 to Analog Mode (for ADC)
  */
  switch (pin) {
  case GpioPin::LED_GREEN:
    printf("[GPIO] Init Green LED as output\n");
    break;
  case GpioPin::LED_YELLOW:
    printf("[GPIO] Init Yellow LED as output\n");
    break;
  case GpioPin::LED_RED:
    printf("[GPIO] Init Red LED as output\n");
    break;
  }
}

void Gpio_WritePin(GpioPin pin, bool state) {
  // Real code: set or clear ODR bit
  /* (Output Data Register) - Setting a GPIO Pin HIGH or LOW
  ** GPIOA->ODR |= (1 << 5);  // Set PA5 HIGH (LED ON)
  ** GPIOA->ODR &= ~(1 << 5); // Set PA5 LOW (LED OFF)
  ** Instead of ODR, STM32 strongly recommends using BSRR (Bit Set/Reset
  ** Register),because: BSRR writes HIGH/LOW in one atomic instruction (no
  **  read-modify-write issue). The GPIOx_BSRR register is 32-bits wide.
  ** The lower 16 bits (BSRR[15:0]) are used to set a pin HIGH.
  ** The upper 16 bits (BSRR[31:16]) are used to reset a pin LOW.
  ** GPIOA->BSRR = (1 << 5); / Set PA5 HIGH
  ** GPIOA->BSRR = (1 << (5 + 16)); // Set PA5 LOW

  */
  switch (pin) {
  case GpioPin::LED_GREEN:
    if (state)
      printf("Green ON\n");
    else
      printf("Green OFF\n");
    break;
  case GpioPin::LED_YELLOW:
    if (state)
      printf("Yellow ON\n");
    else
      printf("Yellow OFF\n");
    break;
  case GpioPin::LED_RED:
    if (state)
      printf("Red ON\n");
    else
      printf("Red OFF\n");
    break;
  }
}
