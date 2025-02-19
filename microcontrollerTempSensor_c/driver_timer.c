#include "driver_timer.h"
#include <stdio.h>

static TimerCallback s_timerCallback = 0;

void Timer_Init100us(TimerCallback cb) {
  s_timerCallback = cb;
  // In real code, configure TIMx for 10kHz update event
  // TIMx->PSC, TIMx->ARR, etc.
  printf("[Timer] 10kHz init (mock)\n");
}

// For demonstration on PC,simulate the timer interrupt
void Timer_SimulateTick() {
  if (s_timerCallback) {
    s_timerCallback();
  }
}
