#pragma once

#include "temperatureSensor.h"

class RevBSensor : public TemperatureSensor {
public:
  RevBSensor();
  ~RevBSensor() override {}

  void init() override;
  void startSampling() override;
  void setCallback(TemperatureReadyCallback callBack) override;

private:
  TemperatureReadyCallback m_callback;
  static void adcCallback(uint16_t rawValue);
};
