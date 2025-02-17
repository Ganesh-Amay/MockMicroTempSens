#pragma once

#include <cstdint>
#include <functional>

// Callback type for the timer interrupt
using TimerCallback = std::function<void()>;

// Initialize a hardware timer to trigger at 100 microseconds (10 kHz).
void Timer_Init100us(TimerCallback cb);

// Mock function to simulate the timer's main loop or interrupt trigger in PC
// code
void Timer_SimulateTick();
