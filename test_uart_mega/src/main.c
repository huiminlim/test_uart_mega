#include <asf.h>
#include <avr/io.h>
#include <delay.h>
#include <string.h>
#include <avr/sfr_defs.h>			// For loop_until_bit_is_set()

#define FF_CPU 16000000UL
#define BAUD 9600
#define BRC ((FF_CPU/16/BAUD) - 1)

void uart1_init(void);
void uart1_tx_char(char c);
void uart1_tx_string(char str[]);

void uart1_init(void) {
    UBRR1H = (BRC >> 8);
    UBRR1L = BRC;

    UCSR1B = (1 << TXEN1);

    UCSR1C = (1 << UCSZ00) | (1 << UCSZ11);
}

void uart1_tx_char(char c) {
    loop_until_bit_is_set(UCSR1A, UDRE1);
    UDR1 = c;
}

void uart1_tx_string(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        uart1_tx_char(str[i]);
    }

    uart1_tx_char('\r');
    uart1_tx_char('\n');
}

int main (void) {
    board_init();

    uart1_init();

    while (1) {
        //uart1_tx_char('8');
        uart1_tx_string("hello");
        delay_ms(1000);
    }

}
