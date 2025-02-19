#pragma once

#include "temperatureSensor.h"

class RevASensor : public TemperatureSensor {

public:
  RevASensor();
  ~RevASensor() override {}

  void init() override;
  void startSampling() override;
  void setCallback(TemperatureReadyCallback callBack) override;
  void processData() override;

private:
  TemperatureReadyCallback m_callback;
  static void adcCallback(uint16_t rawValue);
};
