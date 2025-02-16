#pragma once

#include <cstdint>
#include <functional>

// Called when a new temperature reading is ready.
using TemperatureReadyCallback = std::function<void(float)>;

class TemperatureSensor {
public:
  virtual ~TemperatureSensor() {}

  // Called once to set up ADC for this sensor
  virtual void init() = 0;

  // Optionally start sampling or just rely on ADC triggers
  virtual void startSampling() = 0;

  // Provide a way to set user callback
  virtual void setCallback(TemperatureReadyCallback callBack) = 0;
};
