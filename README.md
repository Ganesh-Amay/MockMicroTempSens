# Embedded Temperature Monitoring (Mock) Project

This repository demonstrates a **bare-metal style** temperature monitoring system, designed for an STM32-like microcontroller but **mocked** to run on a PC. 

**Two** variants are provided:

1. **C++ Version**: Uses classes (`RevASensor`, `RevBSensor`, etc.) and `std::function` for callbacks.
2. **C Version**

## Project Structure

. ├─ cplusplus_version/ │ ├─ Makefile │ ├─ main.cpp │ ├─ driver_clock.h/.cpp │ ├─ driver_timer.h/.cpp │ ├─ driver_adc.h/.cpp │ ├─ driver_gpio.h/.cpp │ ├─ driver_eeprom.h/.cpp │ ├─ temperatureSensor.h/.cpp │ ├─ revASensor.h/.cpp │ ├─ revBSensor.h/.cpp │ ├─ ledController.h/.cpp │ └─ ... ├─ pure_c_version/ │ ├─ Makefile │ ├─ main.c │ ├─ driver_clock.h/.c │ ├─ driver_timer.h/.c │ ├─ driver_adc.h/.c │ ├─ driver_gpio.h/.c │ ├─ driver_eeprom.h/.c │ ├─ temperatureSensor.h │ ├─ revASensor.h/.c │ ├─ revBSensor.h/.c │ ├─ ledController.h/.c │ └─ system_architecture.pdf.. └─ README.md 

### Files

- **`driver_*.*`**: Mock drivers for clock, timer, ADC, GPIO, and EEPROM.  
- **`temperatureSensor.*`**: Common interface or base class for temperature sensors.  
- **`revASensor.*`, `revBSensor.*`**: Implementations for different resolution sensors.  
- **`ledController.*`**: Logic to drive LEDs based on temperature thresholds.  
- **`main.*`**: Orchestrates everything (reads EEPROM, picks sensor, configures timer, etc.).  
- **`Makefile`**: Builds the code into a native executable on a PC.

## Building & Running

### 1. C++ Version

1. **Navigate** to `microcontrollerTempSensor_cpp/`.  
2. **Build** by running:
   ```bash
   make

### Run the generated executable:
./demo

### 2. C Version

1. **Navigate** to `microcontrollerTempSensor_c/`.
2. **Build** by running:
   ```bash
   make

### Run the generated executable:
./demo
   
