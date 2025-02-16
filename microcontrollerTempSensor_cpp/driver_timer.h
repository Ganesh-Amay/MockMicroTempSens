#pragma once

#include <cstdint>

// Callback type for the timer interrupt
typedef void (*TimerCallback)();

// Initialize a hardware timer to trigger at 100 microseconds (10 kHz).
void Timer_Init100us(TimerCallback cb);

// Mock function to simulate the timer's main loop or interrupt trigger in PC code
void Timer_SimulateTick();
