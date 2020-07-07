#ifndef F_CPU 
#define F_CPU 16000000UL
#endif 

#include "spi_lib/spi_comm.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


#define RFM95_ID_REG 0x01

uint8_t rx_buffer;

int main(void)
{
    DDRD = (1<<PORT7);
    spi_master_init();

    while(1)
    {
        
        _delay_ms(3000);
    }
    return 0;
}
