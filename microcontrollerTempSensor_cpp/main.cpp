/* In the purely mock code, the concept of interrupts is
** simulated. Real hardware would have:A Timer ISR that fires
** every 100 µs.An ADC ISR that fires upon conversion completion.
** In actual hardware, this would be an ISR (e.g.TIMx_IRQHandler() on
** STM32).
** Reading or capturing a data register (the ADC value).
** Storing it in a buffer or calling a lightweight callback function that does
** minimal work. Possibly setting a flag  to let the main loop do
** heavier processing. Then return immediately.*/

/*In the sample code:
** we do not show heavy processing.If we did have heavy processing,
** we’d typically do it in main() or a separate function that’s polled
** or triggered by a flag.Because it’s a minimal demonstration,
** the “heavy part” is basically deciding which LED color to turn on*/

/*In a real microcontroller :
** 1.Timer hits compare match(every 100 µs)
** 2.ISR is triggered,CPU context switches.
** 3.In the ISR, we do minimal tasks(e.g., start an ADC conversion or handle a
**   DMA done flag)
** 4.The CPU returns from the ISR quickly.
** 5.Normal code(in main() or RTOS tasks) continues running, sees new data is
available, and performs any heavier computations*/

#include "driver_adc.h"
#include "driver_clock.h"
#include "driver_eeprom.h"
#include "driver_timer.h"
#include "globalFlags.h"
#include "ledController.h"
#include "revASensor.h"
#include "revBSensor.h"
#include "temperatureSensor.h"
#include <cstdint>
#include <cstdio>

namespace {
// Global LED controller
static LedController g_ledController;
constexpr uint8_t nullTerminator{'\0'};

// Callback for temperature data
static void temperatureCallback(float temperatureC) {
  // Update LEDs based on thresholds
  g_ledController.update(temperatureC);
}

// Example Timer interrupt callback: if we're using an interrupt-based
// ADC, we might not need this:Because it’s “fake,” we’re not literally
// in an ISR.
static void onTimerInterrupt() {
  // If we had a software-driven ADC, we'd trigger the ADC here.
  // For demonstration: simulate a sawtooth ADC value from 30..1100
  static uint16_t fakeValue = 30;
  static bool goingUp = true;

  if (goingUp) {
    fakeValue += 10;
    if (fakeValue >= 1100) {
      goingUp = false;
    }
  } else {
    if (fakeValue > 0) {
      fakeValue -= 10;
    }
    if (fakeValue <= 10) {
      goingUp = true;
    }
  }

  // Now call the mock ADC conversion function
  Adc_SimulateConversion(fakeValue);
  // If desired, log something:
  // printf("Timer Tick, ADC Value = %u\n", fakeValue);
}
} // namespace

int main() {
  // Configure system clock (RCC, PLL, flash latency, etc.)
  SystemClock_Config();

  // Initialize I2C-based EEPROM (mock)
  Eeprom_I2C_Init();

  // Read hardware revision from EEPROM
  uint8_t buffer[9] = {0};
  bool ok = Eeprom_ReadBytes(0, buffer, sizeof(buffer));
  if (!ok) {
    printf("EEPROM read failed.\n");
    // handle error
  }
  buffer[8] = nullTerminator;

  // For example: 0=RevA, 1=RevB
  uint8_t hardwareRevision = buffer[0];
  printf("HW Revision: %u\n", hardwareRevision);
  printf("Serial: %s\n", &buffer[1]);

  // Create sensor instance
  TemperatureSensor *sensor = nullptr;
  if (hardwareRevision == 0)
    sensor = new RevASensor();
  else
    sensor = new RevBSensor();

  // Initialize sensor, set callback
  sensor->init();
  sensor->setCallback(temperatureCallback);

  // Initialize LED pins
  g_ledController.init();

  /*As low-jitter sampling is the need (hardware is more precise than
  software-triggered ISR). In STM32, timers can generate hardware triggers for
  the ADC in the following way:
  ** 1.A timer (TIMx) is configured in output compare mode to generate an event
  every 100 µs (10 kHz).eg: TIM2_CH0 event.
  ** 2.This event is routed to the ADC’s external trigger input.
  ** 3.When the ADC receives the trigger signal, it automatically starts a
  conversion.
  ** 4.Once the ADC completes the conversion, it can:
        - Raise an ADC interrupt (ADC_IRQHandler).
        - Use DMA to store the result (without CPU intervention)
  ** Real-time, high-speed ADC sampling should always use a hardware trigger
     to reduce jitter and CPU overhead. Software Trigger CPU starts ADC
     conversion manually in onTimerInterrupt()*/

  // Software Trigger (Manual Start) CPU starts ADC conversion manually in
  // onTimerInterrupt()
  // If using hardware: initialize timer for 10kHz if using interrupt-based
  // approach (If using hardware trigger to ADC, the timer directly triggers
  // ADC,and we might not need onTimerInterrupt() to do anything.)
  Timer_Init100us(onTimerInterrupt);

  // Start ADC sampling (could be interrupt or DMA)
  sensor->startSampling();

  // Main loop
  for (int i = 0; i < 200; i++) {
    // Simulate or handle other tasks, then WFI in real code:
    // __asm__("WFI"); // Wait for interrupt on real hardware
    // Process ADC data in main loop
      if (newDataAvailable) {
        sensor->processData();
      }
    // For PC mock, let's just artificially call the timer "tick" and ADC
    // simulate: calls onTimerInterrupt
    Timer_SimulateTick();
  }

  // Clean up
  delete sensor;

  return 0;
}
