CXX       := g++
CXXFLAGS  := -std=c++23 -Wall -Wextra -I .
SOURCES   := main.cpp \
               driver_clock.cpp driver_timer.cpp driver_adc.cpp driver_gpio.cpp driver_eeprom.cpp \
               revASensor.cpp revBSensor.cpp ledController.cpp
TARGET    := demo

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

