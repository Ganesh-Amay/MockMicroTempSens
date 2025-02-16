#include "driver_adc.h"
#include <cstdio>

namespace {
// For demonstration, choose interrupt or DMA approach via a constexpr var
// Set to true for DMA mode
constexpr bool UseDma{false};

static AdcCallback s_adcCallback = nullptr;

// single channel for DMA mode
// static uint16_t s_dmaBuffer[1];

} // namespace

// In real code, configure ADC in single-channel mode,
// set external trigger from Timer, etc.
// Step 2 : Configure ADC to Use TIM2 as Trigger
// RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC clock
// ADC1->CFGR |= ADC_CFGR_EXTSEL_3;    // Select TIM2_TRGO as external trigger
// ADC1->CFGR |= ADC_CFGR_EXTEN_0; // Enable hardware triggering on rising
// edge ADC1->CR |= ADC_CR_ADEN;        // Enable ADC
void Adc_Init(AdcCallback callBack) {
  s_adcCallback = callBack;
  printf("[ADC] Init with timer trigger (mock)\n");
}

/* Steps to Enable ADC + DMA
 ** 1	Enable DMA clock (`RCC->AHB1ENR
 ** 2	Set DMA stream to handle ADC (DMAx_Streamy)
 ** 3	Configure DMA direction (peripheral-to-memory)
 ** 4	Set DMA buffer location (s_dmaBuffer[])
 ** 5	Enable ADC DMA mode (ADC_CR2 )
 ** 6	Enable ADC continuous mode (ADC_CR2)
 ** 7	Start ADC conversion (ADC_CR2)
 */
void Adc_Start() {
  if constexpr (UseDma) {
    // Configure DMA for ADC => s_dmaBuffer
    // Enable DMA, set ADC->CR bits, etc.
    printf("[ADC] Start (DMA enabled)\n");
  } else {
    printf("[ADC] Start (interrupt mode)\n");
  }
}

// This function is used in the PC mock to simulate an ADC conversion
void Adc_SimulateConversion(uint16_t mockValue) {
  if constexpr (UseDma) {
    // DMA would place the data in s_dmaBuffer automatically
    // s_dmaBuffer[0] = mockValue;
    // Then eventually a DMA Transfer Complete Interrupt (TCIF)  or
    // Half-Transfer Interrupt (HTIF) interrupt

    // if (s_adcCallback) {
    //   s_adcCallback(s_dmaBuffer[0]);
    // }
  } else {
    // In interrupt mode, the ADC interrupt calls the callback
    if (s_adcCallback) {
      s_adcCallback(mockValue);
    }
  }
}
