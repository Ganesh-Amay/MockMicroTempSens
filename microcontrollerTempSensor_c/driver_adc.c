#include "driver_adc.h"
#include <stdio.h>

// For demonstration, choose interrupt or DMA approach via a #define
// #define USE_DMA 1

static AdcCallback s_adcCallback = 0;

void Adc_Init(AdcCallback cb) {
  s_adcCallback = cb;
  // In real code, configure ADC in single-channel mode,
  // set external trigger from Timer, etc.
  printf("[ADC] Init with timer trigger (mock)\n");
}

void Adc_Start() {
#ifdef USE_DMA
  // Configure DMA for ADC => s_dmaBuffer
  // Enable DMA, set ADC->CR bits, etc.
  printf("[ADC] Start (DMA enabled)\n");
#else
  printf("[ADC] Start (interrupt mode)\n");
#endif
}

// This function is used in the PC mock to simulate an ADC conversion
void Adc_SimulateConversion(uint16_t mockValue) {
#ifdef USE_DMA
  // DMA would place the data in s_dmaBuffer automatically
  s_dmaBuffer[0] = mockValue;
  // Then eventually a DMA transfer complete interrupt or half-transfer
  // interrupt
  if (s_adcCallback) {
    s_adcCallback(s_dmaBuffer[0]);
  }
#else
  // In interrupt mode, the ADC interrupt calls the callback
  if (s_adcCallback) {
    s_adcCallback(mockValue);
  }
#endif
}
