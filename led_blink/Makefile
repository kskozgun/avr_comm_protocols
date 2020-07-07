MCU_TYPE = atmega328p
CC = avr-gcc
SRC = led_blink


all: compile link hex flash

compile:
	$(CC) -g -Os -mmcu=$(MCU_TYPE) -c $(SRC).c 

link:
	$(CC) -g -mmcu=$(MCU_TYPE) -o $(SRC).elf $(SRC).o

hex:
	avr-objcopy -j .text -j .data -O ihex $(SRC).elf $(SRC).hex

flash:
	avrdude -p m328p -c usbtiny -U flash:w:led_blink.hex