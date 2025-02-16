#include "driver_timer.h"
#include <cstdio>

static TimerCallback s_timerCallback = nullptr;

void Timer_Init100us(TimerCallback cb) {
  s_timerCallback = cb;
  // In real code, configure TIMx for 10kHz update event
  // TIMx->PSC, TIMx->ARR, etc.
  printf("[Timer] 10kHz init (mock)\n");

  /* Step 1: Configure Timer (TIMx) to Trigger at 10 kHz
  ** Timer Frequency = System Clock / (PSC + 1)
  ** Timer Frequency = 16 MHz / 16 = 1 MHz
  ** Now, the timer counts at 1 MHz, meaning each timer tick is 1 µs.
  ** If you need a 100 µs period, then the auto-reload value (ARR) should count
  ** 100 ticks before resetting.
  ** Timer Period = (ARR + 1) / Timer Frequency
  ** 100 µs      = (100) / 1 MHz */

  //   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable TIM2 clock
  //   TIM2->PSC = 16 - 1;  // Prescaler (assuming 16 MHz clock, makes it 1 MHz)
  //   TIM2->ARR = 100 - 1; // Auto-reload value for 10 kHz (100 µs)
  //   TIM2->CR2 |= TIM_CR2_MMS_1; // TRGO Update event as trigger output
  //   TIM2->CR1 |= TIM_CR1_CEN;   // Start the timer
}

// For demonstration on PC, we simulate the timer interrupt
void Timer_SimulateTick() {
  if (s_timerCallback) {
    s_timerCallback();
  }
}
