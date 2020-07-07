#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // PORTB 5 OUTPUT - Arduino Led Pin 
    DDRD = 0b10000000;

    while(1)
    {
        //PORTD = (1<<PORT7);
        //_delay_ms(1000);
        //PORTD = (0<<PORT7);
        //_delay_ms(1000);
        PORTD ^= 0x80;
        _delay_ms(1000);
    }
    return 0;
}

