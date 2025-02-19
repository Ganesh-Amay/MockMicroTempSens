CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -O2 -I .
SOURCES   := main.c \
               driver_clock.c driver_timer.c driver_adc.c driver_gpio.c driver_eeprom.c \
               revASensor.c revBSensor.c ledController.c global_flags.c adcBuffer.c
TARGET    := demo

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

