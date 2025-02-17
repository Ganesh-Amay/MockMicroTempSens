#include "revBSensor.h"
#include "driver_adc.h"
#include "globalFlags.h"
#include <atomic>
#include <cstdio>

namespace {
constexpr size_t BUFFER_SIZE{64};
// Circular buffer for ADC values
static uint16_t adcBuffer[BUFFER_SIZE];
// Ring buffer indices
static size_t head{0}, tail{0};
} // namespace

RevBSensor::RevBSensor() : m_callback(nullptr) {}

void RevBSensor::init() {
  // Store ADC result in ISR, process in main loop
  Adc_Init([this](uint16_t rawValue) {
    // Store result in circular buffer
    adcBuffer[head] = rawValue;
    // Advance head, wrap if needed
    head = (head + 1) % BUFFER_SIZE;
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
  // Process all new samples
  while (tail != head) {
    uint16_t value = adcBuffer[tail];
    // Move buffer tail forward
    tail = (tail + 1) % BUFFER_SIZE;
    float temperature = static_cast<float>(value) * 0.1f;
    if (m_callback) {
      m_callback(temperature);
    }
  }
  // Reset flag when all data is processed
  newDataAvailable = false;
}