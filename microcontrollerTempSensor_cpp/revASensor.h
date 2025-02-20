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
  // // Static pointer to track the instance
  // static RevASensor *s_activeSensor;
  // // Static function
  // static void adcCallback(uint16_t rawValue);
};
