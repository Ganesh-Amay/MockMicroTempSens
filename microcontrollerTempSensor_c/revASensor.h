#ifndef REV_A_SENSOR_H
#define REV_A_SENSOR_H

#include <stdint.h>

// Define a callback type for temperature readings.
typedef void (*TemperatureReadyCallback)(float temperature);

typedef struct {
  TemperatureReadyCallback cb;
} RevASensor;

// Public API for RevA sensor.
void RevASensor_init();
void RevASensor_startSampling();
void RevASensor_setCallback(RevASensor *sensor, TemperatureReadyCallback cb);
void RevASensor_processData(RevASensor *sensor);

#endif // REV_A_SENSOR_H
