#pragma once

#include <cstddef>
#include <cstdint>

namespace ADCBuffer {
constexpr size_t BUFFER_SIZE{64};
extern uint16_t adcBuffer[BUFFER_SIZE];
extern size_t head;
extern size_t tail;
} // namespace ADCBuffer
