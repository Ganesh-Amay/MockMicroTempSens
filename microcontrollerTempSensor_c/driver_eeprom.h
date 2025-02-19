#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Minimal I2C/EEPROM mock
bool Eeprom_ReadBytes(size_t address, uint8_t *buffer, size_t length);
void Eeprom_I2C_Init();