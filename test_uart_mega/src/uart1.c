/*
    uart1.c

    Created: 17/1/2021 3:36:15 PM
    Author: user
*/
#include <uart1.h>

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