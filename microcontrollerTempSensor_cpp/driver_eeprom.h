#pragma once

#include <cstddef>
#include <cstdint>


// Minimal I2C/EEPROM mock
bool Eeprom_ReadBytes(std::size_t address, std::uint8_t *buffer,
                      std::size_t length);
void Eeprom_I2C_Init();