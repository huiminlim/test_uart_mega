#include <asf.h>

#include <avr/io.h>

#define FF_CPU 16000000UL
#define BAUD 9600
#define BRC ((FF_CPU/16/BAUD) - 1)

#include <delay.h>

int main (void) {
    /* Insert system clock initialization code here (sysclk_init()). */

    board_init();

    /* Insert application code here, after the board has been initialized. */

    UBRR1H = (BRC >> 8);
    UBRR1L = BRC;

    UCSR1B = (1 << TXEN1);

    UCSR1C = (1 << UCSZ00) | (1 << UCSZ11);

    while (1) {
        UDR1 = '8';
        delay_ms(1000);
    }

}
