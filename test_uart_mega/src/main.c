#include <asf.h>
#include <avr/interrupt.h>
#include <delay.h>
#include <uart1.h>
#include <uart.h>

int main (void) {
    board_init();

    // Baud rate = 57600
    uart_init();

    // Baud rate = 9600
    uart1_init();
    sei(); // Turn on external interrupts



    while (1) {
        const char *s = uart1_rx_string();

        if (strcmp("random", s) != 0) {
            printf("string is: %s\r\n", s);
        }
    }
}
