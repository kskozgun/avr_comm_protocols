#ifndef F_CPU 
#define F_CPU 16000000UL
#endif 

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include "uart_comm.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define RFM95_ID_REG 0x01

unsigned char *data = "Hi from atmega 328";

uint8_t rx_buffer;

int main(void)
{
    uart_init(MYUBRR);
    //DDRB= (1<<PORT5);
    while(1)
    {
        uart_transmit(data, 18);
        _delay_ms(3000);
    }
    return 0;
}
