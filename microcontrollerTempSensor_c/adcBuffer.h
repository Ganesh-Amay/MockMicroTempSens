#ifndef ADC_BUFFER_H
#define ADC_BUFFER_H

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 64

extern uint16_t adcBuffer[BUFFER_SIZE];
extern size_t head;
extern size_t tail;

#endif // ADC_BUFFER_H
