#include "revBSensor.h"
#include "adcBuffer.h"
#include "driver_adc.h"
#include "globalFlags.h"
#include <cstdio>

RevBSensor::RevBSensor() : m_callback(nullptr) {}

void RevBSensor::init() {
  // Store ADC result in ISR, process in main loop
  Adc_Init([this](uint16_t rawValue) {
    // Store result in circular buffer
    ADCBuffer::adcBuffer[ADCBuffer::head] = rawValue;
    // Advance ADCBuffer::head, wrap if needed
    ADCBuffer::head = (ADCBuffer::head + 1) % ADCBuffer::BUFFER_SIZE;
    // Signal new data available
    newDataAvailable = true;
  });

  printf("[RevB Sensor] Initialized (1 °C per digit).\n");
}

void RevBSensor::startSampling() {
  Adc_Start();
  printf("[RevB Sensor] startSampling called.\n");
}

void RevBSensor::setCallback(TemperatureReadyCallback callBack) {
  m_callback = callBack;
}

// Process ADC data outside ISR
void RevBSensor::processData() {
  while (ADCBuffer::tail != ADCBuffer::head) {
    // Process all new samples
    uint16_t value = ADCBuffer::adcBuffer[ADCBuffer::tail];
    ADCBuffer::tail = (ADCBuffer::tail + 1) % ADCBuffer::BUFFER_SIZE;
    float temperature = static_cast<float>(value);
    if (m_callback) {
      m_callback(temperature);
    }
  }
  // Reset flag when all data is processed
  newDataAvailable = false;
}
