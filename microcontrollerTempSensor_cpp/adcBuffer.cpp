#include "adcBuffer.h"

namespace ADCBuffer {
uint16_t adcBuffer[BUFFER_SIZE];
size_t head{0};
size_t tail{0};
} // namespace ADCBuffer
