#include "revBSensor.h"
#include "driver_adc.h"
#include <cstdio>

static RevBSensor *s_activeSensorB = nullptr;

RevBSensor::RevBSensor() : m_callback(nullptr) {}

void RevBSensor::init() {
  s_activeSensorB = this;
  Adc_Init(adcCallback);
  printf("[RevB Sensor] Initialized (0.1 °C per digit).\n");
}

void RevBSensor::startSampling() {
  Adc_Start();
  printf("[RevB Sensor] startSampling called.\n");
}

void RevBSensor::setCallback(TemperatureReadyCallback callBack) {
  m_callback = callBack;
}

// This static function is called by the ADC driver
void RevBSensor::adcCallback(uint16_t rawValue) {
  if (s_activeSensorB) {
    // 1 digit = 0.1°C => rawValue * 0.1
    float temperature = static_cast<float>(rawValue) * 0.1f;
    s_activeSensorB->m_callback(temperature);
  }
}
