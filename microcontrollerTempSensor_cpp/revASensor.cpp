#include "revASensor.h"
#include "driver_adc.h"
#include "globalFlags.h"
#include <cstdio>

namespace {
constexpr size_t BUFFER_SIZE{64};
// Circular buffer for ADC values
static uint16_t adcBuffer[BUFFER_SIZE];
// Ring buffer indices
static size_t head{0}, tail{0};
} // namespace

RevASensor::RevASensor() : m_callback(nullptr) {}

void RevASensor::init() {
  // Store ADC result in ISR, process in main loop
  Adc_Init([this](uint16_t rawValue) {
    // Store result in circular buffer
    adcBuffer[head] = rawValue;
    // Advance head, wrap if needed
    head = (head + 1) % BUFFER_SIZE;
    // Signal new data available
    newDataAvailable = true;
  });

  printf("[RevA Sensor] Initialized (1 °C per digit).\n");
}

void RevASensor::startSampling() {
  Adc_Start();
  printf("[RevA Sensor] startSampling called.\n");
}

void RevASensor::setCallback(TemperatureReadyCallback callBack) {
  m_callback = callBack;
}

// Process ADC data outside ISR
void RevASensor::processData() {
  while (tail != head) { // Process all new samples
    uint16_t value = adcBuffer[tail];
    tail = (tail + 1) % BUFFER_SIZE; // Move buffer tail forward

    float temperature = static_cast<float>(value);
    if (m_callback) {
      m_callback(temperature);
    }
  }
  newDataAvailable = false; // Reset flag when all data is processed
}
