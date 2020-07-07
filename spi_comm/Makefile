MCU_TYPE = atmega328p
CC = avr-gcc
OUTPUT = main


all: compile link hex flash

compile_spi:
	$(CC) -g -Os -mmcu=$(MCU_TYPE) -c spi_lib/*.c

#compile_lora:
#	$(CC) -g -Os -mmcu=$(MCU_TYPE) -c *.c

link:
	$(CC) -g -Os -mmcu=$(MCU_TYPE) -o $(OUTPUT).elf main.c *.o

hex:
	avr-objcopy -j .text -j .data -O ihex $(OUTPUT).elf $(OUTPUT).hex

flash:
	avrdude -p m328p -c usbtiny -U flash:w:$(OUTPUT).hex

size:
	avr-size -C --mcu=atmega328p main.elf

clean:
	rm *.o
	rm *.elf
	rm *.hex