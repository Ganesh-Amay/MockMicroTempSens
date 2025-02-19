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
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "driver_adc.h"
#include "driver_clock.h"
#include "driver_eeprom.h"
#include "driver_timer.h"
#include "ledController.h"

#include "global_flags.h"
#include "revASensor.h"
#include "revBSensor.h"

static void temperatureCallback(float temperatureC);
static void onTimerInterrupt(void);

typedef union {
  RevASensor sensorA;
  RevBSensor sensorB;
} SensorUnion;

typedef enum { SENSOR_REV_A, SENSOR_REV_B } SensorType;

static SensorType activeSensor;
static SensorUnion sensorStorage;

int main(void) {
  // 1. System Clock
  SystemClock_Config();

  // 2. EEPROM
  Eeprom_I2C_Init();

  // Read hardware revision from mock EEPROM
  uint8_t buffer[9] = {0};
  bool ok = Eeprom_ReadBytes(0, buffer, 8);
  if (!ok) {
    printf("EEPROM read failed.\n");
  }
  buffer[8] = '\0';
  uint8_t hardwareRevision = buffer[0];
  printf("HW Revision: %u\n", hardwareRevision);
  printf("Serial: %s\n", &buffer[1]);

  // 3. Instantiate the correct sensor based on EEPROM value
  if (hardwareRevision == 0) {
    activeSensor = SENSOR_REV_A;
    RevASensor_init();
    // 4. Provide the callback for temperature
    RevASensor_setCallback(&sensorStorage.sensorA, temperatureCallback);
  } else {
    activeSensor = SENSOR_REV_B;
    RevBSensor_init();
    RevBSensor_setCallback(&sensorStorage.sensorB, temperatureCallback);
  }

  // 5. Init LED controller
  LedController_init();

  // 6. Init timer at 10kHz
  Timer_Init100us(onTimerInterrupt);

  // 5. Start ADC sampling for the active sensor.
  switch (activeSensor) {
  case SENSOR_REV_A:
    RevASensor_startSampling();
    break;
  case SENSOR_REV_B:
    RevBSensor_startSampling();
    break;
  default:
    break;
  }

  // 6. Main loop: simulate timer ticks and process ADC data.
  for (int i = 0; i < 200; i++) {
    Timer_SimulateTick();
    if (newDataAvailable) {
      switch (activeSensor) {
      case SENSOR_REV_A:
        RevASensor_processData(&sensorStorage.sensorA);
        break;
      case SENSOR_REV_B:
        RevBSensor_processData(&sensorStorage.sensorB);
        break;
      default:
        break;
      }
    }
  }

  return 0;
}

// Called whenever on a new temperature sample
static void temperatureCallback(float temperatureC) {
  // Update LED states
  LedController_update(temperatureC);
}

// Timer interrupt callback (mock). Generate a sawtooth ADC value.
static void onTimerInterrupt(void) {
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
  // Simulate an ADC read
  Adc_SimulateConversion(fakeValue);

  // To see each tick:
  // printf("TimerTick -> ADC=%u\n", fakeValue);
}
