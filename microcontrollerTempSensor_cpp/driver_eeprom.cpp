#include "driver_eeprom.h"
#include <cstdio>

// For demonstration, keep a mock buffer
namespace {
constexpr uint8_t hardwareRevA{0x00};
constexpr uint8_t hardwareRevB{0x01};
constexpr uint8_t hardwareRev{hardwareRevA};
constexpr uint8_t letterA{'A'};
constexpr uint8_t letterB{'B'};
constexpr uint8_t letterC{'C'};
constexpr uint8_t digit1{'1'};
constexpr uint8_t digit2{'2'};
constexpr uint8_t digit3{'3'};
constexpr uint8_t digit4{'4'};
constexpr uint8_t nullTerminator{'\0'};
constexpr uint8_t s_mockEepromData[16] = {hardwareRev, letterA, letterB,
                                          letterC,     digit1,  digit2,
                                          digit3,      digit4,  nullTerminator};
} // namespace

/* In real code, configure I2C SCL/SDA pins, speed, etc.
 ** 1. Configure I2C GPIO Pins(SCL and SDA)
 ** 2. Enable the I2C Peripheral
 ** 3. Set the I2C Speed(Standard 100 kHz [General sensors, EEPROMs] or Fast 400
 **    kHz[Faster communication (e.g., LCD, high-speed sensors)])
 ** 4. Implement I2C Transactions(Start, Write Address, Read Data, Stop)
 ** 5. For STM32 using HSI16 (16 MHz system clock), use the I2C_TIMINGR register
 **    to set timing values.
 **    a) Prescaler (PRESC): Divides system clock.
 **    b) SCLH/SCLL: Defines High and Low times of the clock.*/
void Eeprom_I2C_Init() {
  // mock code
  printf("[I2C] Eeprom initialization (mock)\n");
}

bool Eeprom_ReadBytes(std::size_t address, std::uint8_t *buffer,
                      std::size_t length) {
  // In real code, send I2C start, device address, memory address, then
  // read.
  printf("[I2C] Eeprom Read (mock)\n");

  // Validate address range in this mock
  if (address + length > sizeof(s_mockEepromData)) {
    return false;
  }
  for (std::size_t i = 0; i < length; i++) {
    buffer[i] = s_mockEepromData[address + i];
  }
  return true;
}
