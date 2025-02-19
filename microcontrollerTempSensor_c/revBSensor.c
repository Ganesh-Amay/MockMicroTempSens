#include "revBSensor.h"
#include "adcBuffer.h"
#include "driver_adc.h"
#include "global_flags.h"
#include <stdio.h>

static void revB_adcCallback(uint16_t rawValue) {
  adcBuffer[head] = rawValue;
  head = (head + 1) % BUFFER_SIZE;
  newDataAvailable = true;
}

void RevBSensor_init() {
  Adc_Init(revB_adcCallback);
  printf("[RevB Sensor] Initialized (0.1 °C per digit).\n");
}

void RevBSensor_startSampling() {
  printf("[RevB Sensor] Start Sampling called.\n");
  Adc_Start();
}

void RevBSensor_setCallback(RevBSensor *sensor, TemperatureReadyCallback cb) {
  sensor->cb = cb;
}

void RevBSensor_processData(RevBSensor *sensor) {
  while (tail != head) {
    uint16_t value = adcBuffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    // RevB conversion: 0.1 °C per digit
    float temperature = (float)value * 0.1f;
    if (sensor->cb) {
      sensor->cb(temperature);
    }
  }
  newDataAvailable = false;
}
