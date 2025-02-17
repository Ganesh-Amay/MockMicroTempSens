#pragma once

#include <cstdint>
#include <functional>

// Initialize the ADC, set up single channel, triggered by the timer, etc.
void Adc_Init(std::function<void(uint16_t)> callBack);

// Start the ADC conversion process (on real hardware, this may be automatic
// once triggered)
void Adc_Start();

// Mock function to simulate a single ADC conversion cycle (in real MCU, done by
// hardware)
void Adc_SimulateConversion(uint16_t mockValue);
