#include "revASensor.h"
#include "driver_adc.h"
#include <cstdio>

static RevASensor *s_activeSensorA = nullptr;

RevASensor::RevASensor() : m_callback{nullptr} {}

void RevASensor::init() {
  s_activeSensorA = this;
  Adc_Init(adcCallback);
  printf("[RevA Sensor] Initialized (1 °C per digit).");
}

void RevASensor::startSampling() {
  Adc_Start();
  printf("[RevA Sensor] startSampling called.\n");
}

void RevASensor::setCallback(TemperatureReadyCallback callBack) {
  m_callback = callBack;
}

// This static function is called by the ADC driver
void RevASensor::adcCallback(uint16_t rawValue) {
  if (s_activeSensorA) {
    // 1 digit = 1°C, so rawValue is effectively direct Celsius
    float temperature = static_cast<float>(rawValue);
    s_activeSensorA->m_callback(temperature);
  }
}
