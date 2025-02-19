#include "driver_eeprom.h"
#include <stdio.h>

static uint8_t s_mockEepromData[9] = {
    // hardware revision => 0=RevA, 1=RevB
    0x00, 'A', 'B', 'C', '1', '2', '3', '4', '\0'};

// In real code, configure I2C SCL/SDA pins, speed, etc.
void Eeprom_I2C_Init() {
  // E.g., configure I2C peripheral for 100 kHz or 400 kHz
  printf("[I2C] Eeprom initialization (mock)\n");
}

bool Eeprom_ReadBytes(size_t address, uint8_t *buffer, size_t length) {
  // In real code, send I2C start, device address, memory address, then read.
  printf("[I2C] Eeprom Read (mock)\n");

  // Validate address range in this mock
  if (address + length > sizeof(s_mockEepromData)) {
    return false;
  }
  for (size_t i = 0; i < length; i++) {
    buffer[i] = s_mockEepromData[address + i];
  }
  return true;
}
