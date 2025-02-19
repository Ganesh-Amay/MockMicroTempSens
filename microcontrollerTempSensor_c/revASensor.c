#include "revASensor.h"
#include "adcBuffer.h"
#include "driver_adc.h"
#include "global_flags.h"
#include <stdio.h>

// Internal ADC callback for RevA (static limits scope to this file).
static void revA_adcCallback(uint16_t rawValue) {
  adcBuffer[head] = rawValue;
  head = (head + 1) % BUFFER_SIZE;
  newDataAvailable = true;
}

void RevASensor_init() {
  Adc_Init(revA_adcCallback);
  printf("[RevA Sensor] Initialized (1 °C per digit).\n");
}

void RevASensor_startSampling() {
  printf("[RevA Sensor] Start Sampling called.\n");
  Adc_Start();
}

void RevASensor_setCallback(RevASensor *sensor, TemperatureReadyCallback cb) {
  sensor->cb = cb;
}

void RevASensor_processData(RevASensor *sensor) {
  while (tail != head) {
    uint16_t value = adcBuffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    // RevA conversion: 1 digit = 1 °C
    float temperature = (float)value;
    if (sensor->cb) {
      sensor->cb(temperature);
    }
  }
  newDataAvailable = false;
}
