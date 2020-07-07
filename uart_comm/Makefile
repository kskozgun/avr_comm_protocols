MCU_TYPE = atmega328p
CC = avr-gcc
OUTPUT = uart

all: compile hex flash

compile:
	$(CC) -g -Os -mmcu=$(MCU_TYPE) -o $(OUTPUT).elf main.c uart_comm.c

hex:
	avr-objcopy -j .text -j .data -O ihex $(OUTPUT).elf $(OUTPUT).hex

flash:
	avrdude -p m328p -c usbtiny -U flash:w:$(OUTPUT).hex

size:
	avr-size -C --mcu=atmega328p main.elf

clean:
	rm *.elf
	rm *.hex