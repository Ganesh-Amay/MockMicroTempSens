#ifndef REV_B_SENSOR_H
#define REV_B_SENSOR_H

#include <stdint.h>

typedef void (*TemperatureReadyCallback)(float temperature);

typedef struct {
  TemperatureReadyCallback cb;
} RevBSensor;

// Public API for RevB sensor.
void RevBSensor_init();
void RevBSensor_startSampling();
void RevBSensor_setCallback(RevBSensor *sensor, TemperatureReadyCallback cb);
void RevBSensor_processData(RevBSensor *sensor);

#endif // REV_B_SENSOR_H
